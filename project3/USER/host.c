#include "head.h"


int Host_Fun()
{
	int x,y;
	
	while(finger_ctrl == 0)
	{		
		read(finger_fd,&finger,sizeof(finger));
		if(finger.type == EV_ABS && finger.code == ABS_X)  //触屏
			x = finger.value;
		if(finger.type == EV_ABS && finger.code == ABS_Y) 
			y = finger.value;

		if (finger.type == EV_KEY && finger.code == BTN_TOUCH && finger.value != 0 && x>153 && x<243 && y>431 && y<480)
		{
			
			system("arecord -c1 -r16000 -twav -fS16_LE 1.wav &");
	
		}
		if (finger.type == EV_KEY && finger.code == BTN_TOUCH && finger.value == 0 && x>153 && x<243 && y>431 && y<480)
		{
			system("killall -9 arecord");
			File_Snd("1.wav");
		}

		if(finger.type == EV_KEY && finger.code == BTN_TOUCH && finger.value == 0) 
		{

			
			if(x>50 && x<160 && y>370 && y<420)//停车
			{
				Parking = 1;
				printf("开始停车！\n");
				pthread_create(&Card_Node->stop_id,NULL,Stop_Fun,NULL);//创建线程开始计时
				Show_Ascii_Init();
				Show_Ascii(600,270,"Park");
				Show_Ascii_Free();
			}
			if(x>250 && x<360 && y>370 && y<420 && Parking == 1)//取车
			{
				Parking = 0;
				Show_Ascii_Init();
				Show_Ascii(600,270,"Pick");
				sleep(1);
				Show_Ascii(600,270,"    ");
				Show_Ascii_Free();
				pthread_create(&Card_Node->pick_id,NULL,Pick_Fun,NULL);//创建线程停止计时,顺便扣除费用,重新显示余额,不能扣除提示
			}
			if(x>425 && x<535 && y>370 && y<420)//充值
			{
				Charge_Fun();
			}
			if(x>625 && x<735 && y>370 && y<420)//报警
			{
					beep_set();//打开蜂鸣器
			}

			

			if(x>361 && x<437 && y>431 && y<480)//开启摄像头
			{
					camera();
			}


			if(x>740 && x<800 && y>0 && y<58)//退出
			{
				printf("退出！\n");
				Show_Ascii_Init();
				Show_Ascii(600,270,"Eixt");
				sleep(2);
				Show_Ascii(480, 70,"             ");
				Show_Ascii(480,170,"             ");
				Show_Ascii(480,270,"             ");
				Show_Ascii_Free();
				break;
			}


			

		}
	}
	


	return 0 ;
}