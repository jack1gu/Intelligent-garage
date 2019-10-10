#include "head.h"


int Register_Fun()
{
	//打开注册界面
	pic("register.bmp"); 
	finger_ctrl = 1;
	//用户点击屏幕输入字母填写姓名，回车确定输入且返回
	char register_buf[20] = {0};
	int x,y;
	Show_Ascii_Init();
	while(finger_ctrl == 1)
	{
		read(finger_fd,&finger,sizeof(finger));
		if(finger.type == EV_ABS && finger.code == ABS_X)  //触屏
			x = finger.value;
		if(finger.type == EV_ABS && finger.code == ABS_Y) 
			y = finger.value;

		if(finger.type == EV_KEY && finger.code == BTN_TOUCH && finger.value == 0) 
		{				
			if(x>0 && x<80 && y>200 && y<280)//Q
			{
				usleep(3000);
				Show_One_Ascii(120,70,'Q');
				memcpy(&register_buf[num],"Q",1);
				num++;
			}
			if(x>80 && x<160 && y>200 && y<280)//W
			{
				usleep(3000);
				Show_One_Ascii(120,70,'W');
				memcpy(&register_buf[num],"W",1);
				num++;
			}
			if(x>160 && x<240 && y>200 && y<280)//E
			{
				usleep(3000);
				Show_One_Ascii(120,70,'E');
				memcpy(&register_buf[num],"E",1);
				num++;
			}
			if(x>240 && x<320 && y>200 && y<280)//R
			{
				usleep(3000);
				Show_One_Ascii(120,70,'R');
				memcpy(&register_buf[num],"R",1);
				num++;
			}
			if(x>320 && x<400 && y>200 && y<280)//T
			{
				usleep(3000);
				Show_One_Ascii(120,70,'T');
				memcpy(&register_buf[num],"T",1);
				num++;
			}
			if(x>400 && x<480 && y>200 && y<280)//Y
			{
				usleep(3000);
				Show_One_Ascii(120,70,'Y');
				memcpy(&register_buf[num],"Y",1);
				num++;
			}
			if(x>480 && x<560 && y>200 && y<280)//U
			{
				usleep(3000);
				Show_One_Ascii(120,70,'U');
				memcpy(&register_buf[num],"U",1);
				num++;
			}
			if(x>560 && x<640 && y>200 && y<280)//I
			{
				usleep(3000);
				Show_One_Ascii(120,70,'I');
				memcpy(&register_buf[num],"I",1);
				num++;
			}
			if(x>640 && x<720 && y>200 && y<280)//O
			{
				usleep(3000);
				Show_One_Ascii(120,70,'O');
				memcpy(&register_buf[num],"O",1);
				num++;
			}
			if(x>720 && x<800 && y>200 && y<280)//P
			{
				usleep(3000);
				Show_One_Ascii(120,70,'P');
				memcpy(&register_buf[num],"P",1);
				num++;
			}
			if(x>0 && x<80 && y>280 && y<380)//A
			{
				usleep(3000);
				Show_One_Ascii(120,70,'A');
				memcpy(&register_buf[num],"A",1);
				num++;
			}
			if(x>80 && x<160 && y>280 && y<380)//S
			{
				usleep(3000);
				Show_One_Ascii(120,70,'S');
				memcpy(&register_buf[num],"S",1);
				num++;
			}
			if(x>160 && x<240 && y>280 && y<380)//D
			{
				usleep(3000);
				Show_One_Ascii(120,70,'D');
				memcpy(&register_buf[num],"D",1);
				num++;
			}
			if(x>240 && x<320 && y>280 && y<380)//F
			{
				usleep(3000);
				Show_One_Ascii(120,70,'F');
				memcpy(&register_buf[num],"F",1);
				num++;
			}
			if(x>320 && x<400 && y>280 && y<380)//G
			{
				usleep(3000);
				Show_One_Ascii(120,70,'G');
				memcpy(&register_buf[num],"G",1);
				num++;
			}
			if(x>400 && x<480 && y>280 && y<380)//H
			{
				usleep(3000);
				Show_One_Ascii(120,70,'H');
				memcpy(&register_buf[num],"H",1);
				num++;
			}
			if(x>480 && x<560 && y>280 && y<380)//J
			{
				usleep(3000);
				Show_One_Ascii(120,70,'J');
				memcpy(&register_buf[num],"J",1);
				num++;
			}
			if(x>560 && x<640 && y>280 && y<380)//K
			{
				usleep(3000);
				Show_One_Ascii(120,70,'K');
				memcpy(&register_buf[num],"K",1);
				num++;
			}
			if(x>640 && x<720 && y>280 && y<380)//L
			{
				usleep(3000);
				Show_One_Ascii(120,70,'L');
				memcpy(&register_buf[num],"L",1);
				num++;
			}
		
			if(x>0 && x<80 && y>380 && y<480)//Z
			{
				usleep(3000);
				Show_One_Ascii(120,70,'Z');
				memcpy(&register_buf[num],"Z",1);
				num++;
			}
			if(x>80 && x<160 && y>380 && y<480)//X
			{
				usleep(3000);
				Show_One_Ascii(120,70,'X');
				memcpy(&register_buf[num],"X",1);
				num++;
			}
			if(x>160 && x<240 && y>380 && y<480)//C
			{
				usleep(3000);
				Show_One_Ascii(120,70,'C');
				memcpy(&register_buf[num],"C",1);
				num++;
			}
			if(x>240 && x<320 && y>380 && y<480)//V
			{
				usleep(3000);
				Show_One_Ascii(120,70,'V');
				memcpy(&register_buf[num],"V",1);
				num++;
			}
			if(x>320 && x<400 && y>380 && y<480)//B
			{
				usleep(3000);
				Show_One_Ascii(120,70,'B');
				memcpy(&register_buf[num],"B",1);
				num++;
			}
			if(x>400 && x<480 && y>380 && y<480)//N
			{
				usleep(3000);
				Show_One_Ascii(120,70,'N');
				memcpy(&register_buf[num],"N",1);
				num++;
			}
			if(x>480 && x<560 && y>380 && y<480)//M
			{
				usleep(3000);
				Show_One_Ascii(120,70,'M');
				memcpy(&register_buf[num],"M",1);
				num++;
			}
			if(x>560 && x<640 && y>380 && y<480)//Delete
			{
				usleep(3000);
				num--;
				Delete_Ascii(120,70);
				memcpy(&register_buf[num],"\0",1);
			}
			if((x>640 && x<800 && y>380 && y<480) || (x>720 && x<800 && y>280 && y<380))//Enter
			{
				usleep(3000);
				memcpy(&register_buf[num],"\0",1);
				break;
			}
		}
	}
	printf("姓名：%s\n", register_buf);		//测试
	pic("host.bmp");
	finger_ctrl = 0;
	Card_Node = Add_Node();				//创建节点给新卡

	printf("-------------------------------\n");

	sprintf(Card_Node->ID,"%x",ID);			//Card_Node->ID = ID;
	memcpy(Card_Node->name,register_buf,20);
	Card_Node->money = 0;     //刚刚注册没钱
	ID_Insert(sq);           	//写入数据表 
	Rfid_Write();
	

	usleep(50000);
	printf("ID-------%s\n", Card_Node->ID);
	printf("名字--------%s\n",Card_Node->name );
	printf("钱---------%d\n", Card_Node->money);


	char buf_money[20] = {0};
	sprintf(buf_money,"%d",Card_Node->money);
	Show_Ascii_Init();
	Show_Ascii(480, 70,Card_Node->name);
	Show_Ascii(480,170,Card_Node->ID);			//重新显示信息    
	Show_Ascii(480,270,buf_money);
	Show_Ascii_Free();
	return 0;
}
