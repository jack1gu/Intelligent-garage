#include "head.h"


int Charge_Fun()
{
	finger_ctrl = 2;
	usleep(50000);
	pic("charge.bmp");
	

	char charge_buf[20] = {0};
	int x,y;
	Show_Ascii_Init();
	while(finger_ctrl == 2)
	{
		read(finger_fd,&finger,sizeof(finger));
		if(finger.type == EV_ABS && finger.code == ABS_X)  //触屏
			x = finger.value;
		if(finger.type == EV_ABS && finger.code == ABS_Y) 
			y = finger.value;
		if(finger.type == EV_KEY && finger.code == BTN_TOUCH && finger.value == 0) 
		{
			if(x>0 && x<200 && y>380 && y<480)//1
			{
				usleep(3000);
				Show_One_Ascii(120,70,'1');
				memcpy(&charge_buf[num],"1" ,1);
				num++;
			}
			if(x>200 && x<400 && y>380 && y<480)//2
			{
				usleep(3000);
				Show_One_Ascii(120,70,'2');
				memcpy(&charge_buf[num],"2" ,1);
				num++;
			}
			if(x>400 && x<600 && y>380 && y<480)//3
			{
				usleep(3000);
				Show_One_Ascii(120,70,'3');
				memcpy(&charge_buf[num], "3",1);
				num++;
			}
			if(x>0 && x<200 && y>280 && y<380)//4
			{
				usleep(3000);
				Show_One_Ascii(120,70,'4');
				memcpy(&charge_buf[num], "4",1);
				num++;
			}
			if(x>200 && x<400 && y>280 && y<380)//5
			{
				usleep(3000);
				Show_One_Ascii(120,70,'5');
				memcpy(&charge_buf[num],"5",1);
				num++;
			}
			if(x>400 && x<600 && y>280 && y<380)//6
			{
				usleep(3000);
				Show_One_Ascii(120,70,'6');
				memcpy(&charge_buf[num],"6" ,1);
				num++;
			}
			if(x>0 && x<200 && y>180 && y<280)//7
			{
				usleep(3000);
				Show_One_Ascii(120,70,'7');
				memcpy(&charge_buf[num],"7" ,1);
				num++;
			}
			if(x>200 && x<400 && y>180 && y<280)//8
			{
				usleep(3000);
				Show_One_Ascii(120,70,'8');
				memcpy(&charge_buf[num],"8",1);
				num++;
			}
			if(x>400 && x<600 && y>180 && y<280)//9
			{
				usleep(3000);
				Show_One_Ascii(120,70,'9');
				memcpy(&charge_buf[num], "9",1);
				num++;
			}
			if(x>600 && x<800 && y>280 && y<380)//0
			{
				usleep(3000);
				Show_One_Ascii(120,70,'0');
				memcpy(&charge_buf[num],"0" ,1);
				num++;
			}
			if(x>600 && x<800 && y>180 && y<280)//Delete
			{
				usleep(3000);
				num--;
				Delete_Ascii(120,70);
				memcpy(&charge_buf[num],"\0",1);
			}
			if(x>600 && x<800 && y>380 && y<480)//Enter
			{
				usleep(3000);
				memcpy(&charge_buf[num],"\0",1);
				finger_ctrl = 0;
			}
		}		
	}
	pic("host.bmp");
	int cash = 0;
	for (int i = 0; i < strlen(charge_buf); i++)
	{
		int a = pow(10,strlen(charge_buf)-i-1);
		cash = cash + (int)(charge_buf[i]-48)*a;
	}
	Card_Node->money = Card_Node->money + cash;
	ID_Update(sq);
	Rfid_Write();
	char buf_money[20] = {0};
	sprintf(buf_money,"%d",Card_Node->money);
	Show_Ascii_Init();
	Show_Ascii(480, 70,Card_Node->name);
	Show_Ascii(480,170,Card_Node->ID);			//重新显示信息
	Show_Ascii(480,270,buf_money);
	Show_Ascii_Free();



	return 0 ;
}