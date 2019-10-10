#include "head.h"

unsigned char Password[] = {0xff,0xff,0xff,0xff,0xff,0xff};


int Tty_Init()
{
	int tty_fd = open(DEV_PATH,O_RDWR);
	if(tty_fd == -1)
	{
		perror("open ...");

		return -1;
	}

	struct termios new_cfg,olc_cfg;

	int ret = tcgetattr(tty_fd,&olc_cfg);
	if(ret == -1)
	{
		perror("tcgetattr ...");
		return -1;
	}

	cfmakeraw(&new_cfg);

	new_cfg.c_cflag |= CLOCAL | CREAD;

	cfsetispeed(&new_cfg,B9600);
	cfsetospeed(&new_cfg,B9600);

	new_cfg.c_cflag &= ~CSIZE;
	new_cfg.c_cflag |= CS8;

	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_cflag &= ~CSTOPB;

	new_cfg.c_cc[VTIME] = 10;
	new_cfg.c_cc[VMIN]  = 1;

	tcflush(tty_fd,TCIFLUSH);

	tcsetattr(tty_fd,TCSANOW,&new_cfg);

	return tty_fd;
}

/*计算校验和*/
int Count_Bcc(char * send_buf,int loop_num)
{
	unsigned char BCC = 0;

	int i;
	for(i=0; i<loop_num; i++)
	{
		BCC ^= *(send_buf+i);
	}

	return (~BCC);
}

/*发送A命令判断RFID是否能应答*/
int PiccRequest(int tty_fd)
{
 	unsigned char send_buf[7],recv_buf[7];
  	memset(send_buf, 0,7);
	memset(recv_buf,1,7);//
 	 /*配置A命令*/
 	send_buf[0] = 0x07; /*数据帧 的 长度*/
 	send_buf[1] = 0x02; /*设置发送命令位IOS14443A*/
  	send_buf[2] = 0x41; /*A命令类型*/
  	send_buf[3] = 0x01; /*数据长度*/
 	send_buf[4] = 0x52; /*ALL命令*/
 	send_buf[5] = Count_Bcc(send_buf,send_buf[0]-2);
  	send_buf[6] = 0x03;/*设置结束标志*/

   int ret = write(tty_fd,send_buf,send_buf[0]);
    if (ret == -1)
    {
    	printf("请求应答命令发送失败！\n");
    	return -1;
    }

  	read(tty_fd, recv_buf, 8);  	/*等待应答*/
  	if (recv_buf[2] == 0x00)	 	//应答帧状态部分为0 则请求成功
 	{
    //	printf("应答成功！\n");
      	return 1;
  	}
  	return 0;
}

/*防止碰撞*/
int PiccAnticoll(int tty_fd)
{
	unsigned char send_buf[8],recv_buf[8];
	memset(send_buf, 0,8);
	memset(recv_buf,1,8);//
	/*配置A命令*/
	send_buf[0] = 0x08; /*数据帧 的 长度*/
	send_buf[1] = 0x02; /*设置发送命令位IOS14443A*/
	send_buf[2] = 0x42; /*B命令类型*/
	send_buf[3] = 0x02; /*数据长度*/
	send_buf[4] = 0x93;
	send_buf[5] = 0x00;
	send_buf[6] = Count_Bcc(send_buf,send_buf[0]-2);
	send_buf[7] = 0x03;/*设置结束标志*/

	int ret = write(tty_fd,send_buf,send_buf[0]);
	if (ret == -1)
	{
		printf("防碰撞命令发送失败！\n");
		return -1;
	}

	read(tty_fd,recv_buf,10);
	if(recv_buf[2] == 0x00) //先判断是否同一张卡或者卡还在不在
	{
			
		memcpy(ID_SND,&recv_buf[4],4);	//复制存放ID
		ID = (recv_buf[7]<<24) | (recv_buf[6]<<16) | (recv_buf[5]<<8) | recv_buf[4];//手册说了，低字节在前面
		if (ID != ID_cmp)
		{
			Show_Ascii_Init();//清除主界面的信息
			Show_Ascii(480, 70,"             ");
			Show_Ascii(480,170,"             ");
			Show_Ascii(480,270,"             ");
			Show_Ascii_Free();
		}
		ID_cmp = ID;
		printf("ID: %x\n", ID);
		return 1;
	}
  return 0;
}

int CascSelect(int tty_fd)
{
	/*配置规定的数据帧*/
	char send_fun[23],recv_buf[23];

	memset(send_fun,0,23);
	memset(recv_buf,1,23);

	send_fun[0] = 0x0B;//帧长度
	send_fun[1] = 0x02;//ios14443TYPEA
	send_fun[2] = 0x43;//‘C’类型命令
	send_fun[3] = 0x05;//信息长度
	send_fun[4] = 0x93;
	memcpy(&send_fun[5],ID_SND,4);
	send_fun[9] = Count_Bcc(send_fun,send_fun[0]-2); /*计算校验和*/
	send_fun[10] = 0x03;//结束符

	int ret = write(tty_fd,send_fun,send_fun[0]);
	if (ret  == -1)
	{
		printf("选择命令发送失败！\n");
		return -1;
	}

	read(tty_fd,recv_buf,7);
	if (recv_buf[2] == 0x00)
	{
		return 1;
	}
	else
		printf("选择失败！\n");
	return 0;
}


int  PiccAuthKey(int tty_fd)
{
	/*配置规定的数据帧*/
	char send_fun[23],recv_buf[23];

	memset(send_fun,0,23);
	memset(recv_buf,1,23);

	send_fun[0] = 0x12;//帧长度
	send_fun[1] = 0x02;//ios14443TYPEA
	send_fun[2] = 0x46;//‘F’类型命令
	send_fun[3] = 0x0C;//信息长度
	send_fun[4] = 0X60; //密钥A
	memcpy(&send_fun[5],ID_SND,4);
	memcpy(&send_fun[9],Password,6);
	send_fun[15] = data_block; //区域4
	send_fun[16] = Count_Bcc(send_fun,send_fun[0]-2); /*计算校验和*/
	send_fun[17] = 0x03;//结束符

	int ret = write(tty_fd,send_fun,send_fun[0]);
	if (ret == -1)
	{
		printf("密钥命令发送失败！\n");
		return -1;
	}
	read(tty_fd,recv_buf,6);
	if (recv_buf[2] == 0)
	{
		ret = ID_Seek(sq);				//查询数据库里面有没有该卡的信息，没有则创建，有则跳过创建
		if (ret == -1)
		{
			printf("跳转注册界面\n");  	//测试
			
			Register_Fun();  			//跳转注册界面
			camera();					//拍照
		}
		return 1;
	}
	else
		printf("密钥验证失败！\n");
	return 0;
}

int PiccWrite(int tty_fd)
{
	unsigned char send_fun[50],rcv_buf[50];
	memset(send_fun,0,50);
	memset(rcv_buf,1,50);

	

	memcpy(DataWriteBuf,&Card_Node->money,4);
	memcpy(DataWriteBuf+4,&Card_Node->name,10);




	send_fun[0] = 23;//帧长度23
	send_fun[1] = 0x02;//ios14443TYPEA
	send_fun[2] = 'H';//‘H’类型命令
	send_fun[3] = 17;//信息长度17
	send_fun[4] = data_block;
	memcpy(&send_fun[5],DataWriteBuf,16);
	send_fun[21] = Count_Bcc(send_fun,send_fun[0]-2); /*计算校验和*/
	send_fun[22] = 0x03;//结束符

	for (int i = 0; i < 5; ++i)   //写5次，减少写入失败
	{
		int ret = write(tty_fd,send_fun,send_fun[0]);
		if (ret == -1)
		{
			printf("发送写入命令失败！\n");
			return -1;
		}
		read(tty_fd,rcv_buf,6);
		if (rcv_buf[2] == 0)
		{
			printf("写入卡数据成功！\n");
			DATA_WRITE == 0;
			return 1;
		}
		else
			printf("写入失败！\n");
	}
	
	return 0;

}

int  PiccRead(int tty_fd)
{
	/*配置规定的数据帧*/
	char send_fun[23],recv_buf[22];

	memset(send_fun,0,23);
	memset(recv_buf,1,22);

	send_fun[0] = 0x07;//帧长度
	send_fun[1] = 0x02;//ios14443TYPEA
	send_fun[2] = 0x47;//‘G’类型命令
	send_fun[3] = 0x01;//信息长度
	send_fun[4] = data_block;
	send_fun[5] = Count_Bcc(send_fun,send_fun[0]-2); /*计算校验和*/
	send_fun[6] = 0x03;//结束符

	for (int i = 0; i < 5; ++i)
	{
		int ret = write(tty_fd,send_fun,send_fun[0]);
		if (ret == -1)
		{
			printf("发送读取命令失败！\n");
			return -1;
		}
		usleep(50000);
		ret = read(tty_fd,recv_buf,22);
		if (ret == -1)
		{
			printf("读取数据失败！\n");
		}
		if (recv_buf[2] == 0x00)
		{
			memcpy(DataReadBuf,&recv_buf[4],16);
			int read_money ;
			memcpy(&read_money,DataReadBuf,4);
			printf("姓名：%s\n",DataReadBuf+4 );
			printf("余额：%d\n", read_money);
			return 1;
		}
		else
			printf("读取失败！\n");
	}	

	return 0;

}



int Rfid_Write()
{
	while(1)
	{
		usleep(30000);
		int ret = PiccRequest(tty_fd);	 //请求
		if (ret != 1) continue;

		usleep(30000);
		ret = PiccAnticoll(tty_fd);	 //防碰撞		得到ID_SND
		if (ret != 1) continue;

		usleep(30000);
		ret = CascSelect(tty_fd);   //选择
		if (ret != 1) continue;

		usleep(30000);
		ret = PiccAuthKey(tty_fd);  //密钥验证       创建到对应卡的结构体 或 读取到对应卡
		if (ret != 1) continue;

		usleep(30000);
		ret = PiccWrite(tty_fd);
		if (ret != 1)continue;
		break;

	}
	return 0;
}