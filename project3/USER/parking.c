#include "head.h"


void * Stop_Fun(void * arg)		//不断加1 等待取消线程
{

	Card_Node->count = 0;
	while(1)
	{
		sleep(1);
		Card_Node->count++;
	}
}


void * Pick_Fun(void * arg)
{
	
	if ((Card_Node->money - Card_Node->count) >= 0)
	{
		pthread_cancel(Card_Node->stop_id);		//得到count 且取消停车线程 等待扣费
		Card_Node->money = Card_Node->money - Card_Node->count;
		PiccWrite(tty_fd);
		PiccRead(tty_fd);
		printf("扣费成功！\n");
		Show_Ascii_Init();
		Show_Ascii(480,270,"            ");		//先清空一下余额区
		char buf[10] = {0};
		sprintf(buf,"%d",Card_Node->money);
		Show_Ascii(480,270, buf);
		Show_Ascii_Free();
		ID_Update(sq);
	}
	else
	{
		Parking = 1;
		printf("余额不足，请充值！\n"); //然后需要显示在界面上
		Show_Ascii_Init();
		Show_Ascii(600,270,"NO $");
		Show_Ascii_Free();
	}
	pthread_exit(0);
}