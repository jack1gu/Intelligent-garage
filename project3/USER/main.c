#include "head.h"


int main()
{
	finger_fd = open("/dev/input/event0",O_RDONLY); //打开触摸屏界面
	if (finger_fd == -1)
	{
		perror("finger");
		return -1;
	}

//	pid_t x;
//	x = fork();
//	if (x > 0)  	//子进程 负责读取卡片数据
//	{
		//开启程序，进入主界面
		pic("host.bmp");  				//打开主界面
		beep_init();					//蜂鸣器初始化
		Socket_Init();					//socket初始化+创建收信息线程
		tty_fd = Tty_Init();    		//rfid初始化
		head = Create_Node();			//头结点初始化
		Sqlite3_Init();					//sqlite3初始化
		int ret;
	 	sleep(1);
	 	printf("初始化成功！\n");
		while(1)
		{	
			usleep(30000);
			ret = PiccRequest(tty_fd);	 //请求
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

			Host_Fun();								
		}
//	}
/*	
	if (x == 0)  	//父进程 负责控制开发板
	{
		Host_Fun();
		wait(NULL);
	}
*/	
	close(finger_fd);
	return 0;
}