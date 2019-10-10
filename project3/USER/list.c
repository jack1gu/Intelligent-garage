#include "head.h"

P_ci Create_Node()
{
	P_ci node = (P_ci)malloc(sizeof(CI));
	if (node == NULL)
	{
		perror("malloc");
		return NULL;
	}
	node->next == NULL;
	return node;
}



P_ci Add_Node()
{
	P_ci ADD_NODE = Create_Node();

	ADD_NODE->next = head->next;
	head->next = ADD_NODE;
	
	
	return ADD_NODE;
}

int  Display_Node(P_ci head)
{
	if (head == NULL)
	{
		printf("添加的节点\n");
		return -1;
	}
	else
	{
		P_ci new_node = head->next;

		do
		{
			printf("ID号有：%s\n",new_node->ID );
			new_node = new_node->next;
		}while(new_node != NULL);

		printf("\n");
	}
	return 0;
}

P_ci Find_Node(P_ci head)
{
	char buf1[20]={0};
	char buf2[20]={0};
	if(head == NULL)
	{
		printf("头节点为空！\n");
		return NULL;
	}
	else
	{
		P_ci new_node = head;
		do
		{
		//	sprintf(buf1,"%s",new_node->ID);		//代改进  是否再次注册看这边
			sprintf(buf2,"%x",ID);
			printf("1--------%s\n", new_node->ID);
			printf("2--------%s\n", buf2);
			if (strncmp(new_node->ID,buf2,strlen(buf2)) == 0 )		//只有在主界面才显示
				{
					printf("匹配成功！\n");
					if (finger_ctrl == 0)
					{
						sprintf(buf1,"%d",new_node->money);
						Show_Ascii_Init();
						Show_Ascii(480, 70,new_node->name);
						Show_Ascii(480,170,new_node->ID);
						Show_Ascii(480,270,buf1);
						Show_Ascii_Free();
					}
					return new_node;
				}
			else
				{
					new_node = new_node->next;
					bzero(&buf2,sizeof(buf2));
				}
		}while(new_node);
	}
	return NULL;
}
/*
P_ci Node_Init()
{
	head = Create_Node();
	if (head == NULL)
	{
		perror("head");
		return NULL;
	}
	return head;
}
*/