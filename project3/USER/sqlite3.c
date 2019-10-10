#include "head.h"



void Sqlite3_Init()			//初始化数据表
{
	
	int ret = sqlite3_open("./user.db",&sq);
	if (ret != SQLITE_OK)
	{
		printf("打开数据库失败！\n");
	}
	char cmd[100] = "create table user(ID char[20] unique,name char[20],money int)";
	sqlite3_exec(sq,cmd,NULL,NULL,NULL);
	
	char **dbResult; 
	int nRow,nColumn;
	char *msg;
	char Find[50] = "select * from user";
	ret = sqlite3_get_table(sq,Find,&dbResult,&nRow,&nColumn,&msg);
	if (ret != SQLITE_OK)
	{
		printf("查询失败！\n");
	}
	int num = nColumn; //字段值从num开始
	printf("行：%d ，列：%d\n", nColumn,nRow);
	for( int j = 0; j < nRow ; j++ )
    {
    	
        Card_Node = Add_Node();

        printf("-----\n");
        printf("%s",dbResult[num]);
        sprintf(Card_Node->ID,"%s",dbResult[num++]);
        printf("---------------%s---\n", Card_Node->ID);
        printf("%s",dbResult[num]);
        sprintf(Card_Node->name,"%s",dbResult[num++]);
        printf("---------------%s---\n",Card_Node->name);
        printf("%s",dbResult[num]);	//钱
        char buf[50] = {0};
        sprintf(buf,"%s",dbResult[num++]);
        printf("%s,,,%d\n",buf,strlen(buf));
        Card_Node->money = 0;
        for (int i = 0; i < strlen(buf); i++)
		{
			int a = pow(10,strlen(buf)-i-1);
			Card_Node->money = Card_Node->money + (int)(buf[i]-48)*a;
		}
		printf("Card_Node->money:%d\n",Card_Node->money );
		Card_Node = NULL;
		usleep(30000);
		
    }
}
/*
int sqlite3_list_init( void * para, int n_column, char ** column_value, char ** column_name )
{
	printf("kaishi !!\n");
	Add_Node(head);
	printf("JIXU\n");
	memcpy(Card_Node->ID,column_value[0],20);
	
	printf("%s---------------%s\n", column_value[0],Card_Node->ID);
	memcpy(Card_Node->name,column_value[1],20);
	printf("%s---------------%s\n", column_value[1],Card_Node->name);
	char buf[20] = {0};
	sprintf(buf,"%s",column_value[2]);
	printf("buf----%s----\n", buf);
	for (int i = 0; i < strlen(buf); i++)
		{
			int a = pow(10,strlen(buf)-i-1);
			Card_Node->money = Card_Node->money + (int)(buf[i]-48)*a;
		}
	printf("%s---------------%d\n", column_value[2],Card_Node->money);
	printf("=========================================================\n");
	Display_Node(head);

	return 0;//一定要加
}

*/


int ID_Update(sqlite3 *sq)
{
	char cmd[100] = {0};
	sprintf(cmd,"update user set money = %d where ID = \"%s\"",Card_Node->money,Card_Node->ID);
	int ret = sqlite3_exec(sq,cmd,NULL,NULL,NULL);
	if (ret != SQLITE_OK)
	{
		printf("修改金额失败！\n");
	}
}

int ID_Insert(sqlite3 *sq)
{
	char cmd[100] = {0};
	sprintf(cmd,"insert into user values(\"%s\",\"%s\",%d)",Card_Node->ID,Card_Node->name,Card_Node->money);
	printf("%s\n", cmd);
	Rfid_Write();
	int ret = sqlite3_exec(sq,cmd,NULL,NULL,NULL);
	if (ret != SQLITE_OK)
	{
		printf("添加ID数据表失败！\n");
	}
	return 0;
}

int ID_Seek(sqlite3 *sq)
{
	char cmd[100] = "select * from user";
//	sprintf(cmd,"select * from user where ID = \"%x\"",ID);

//	printf("%s\n",cmd );	//测试
	Card_Node = Find_Node(head);
	int ret = sqlite3_exec(sq,cmd,get_result,NULL,NULL);
	
	if (Card_Node == NULL)
	{
		return -1;
	}

	
	return 0;
}

int get_result( void * para, int n_column, char ** column_value, char ** column_name )
{

	printf("卡号:%s-----姓名:%s-------余额:%s\n", column_value[0],column_value[1],column_value[2]);	//测试
	
	if (Card_Node != NULL && strcmp(Card_Node->ID,column_value[0]) == 0)
	{
		memcpy(Card_Node->name,column_value[1],20);
		char buf[20] = {0};
		Card_Node->money = 0;
		sprintf(buf,"%s",column_value[2]);
		for (int i = 0; i < strlen(buf); i++)
			{
				int a = pow(10,strlen(buf)-i-1);
				Card_Node->money = Card_Node->money + (int)(buf[i]-48)*a;
			}
		
	}
	
	

	return 0;//一定要加
}	


int Sqlite3_Free(sqlite3 *sq)
{
	char end[50] = "drop table user";
	int ret = sqlite3_exec(sq,end,NULL,NULL,NULL);	//删除表 测试用
	if (ret == SQLITE_OK)
	{
		printf("删除表成功！\n");
	}

	ret = sqlite3_close(sq);
	if (ret != SQLITE_OK)
	{
		printf("关闭数据库失败！\n");
	}

	return 0;
}