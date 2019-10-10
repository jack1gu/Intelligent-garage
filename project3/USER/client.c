#include "head.h"




int Socket_Init()
{
	c_fd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in c_addr;
	bzero(&c_addr,sizeof(c_addr));
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(8888);
	c_addr.sin_addr.s_addr = inet_addr(SERVER);

	while(1)
	{
		int ret = connect(c_fd,(struct sockaddr *)&c_addr,sizeof(c_addr));
		if (ret == -1)
		{
			perror("connect");
		}
		else
			break;
		sleep(2);
	}
	sleep(1);
	pthread_create(&msg_id,NULL,Msg_Rcv,NULL);

	return 0;
}

int File_Snd(char *path_snd)
{
	FILE * fd = fopen(path_snd,"r");
	if (fd == NULL)
	{
		perror("fopen");
		return -1;
	}
	fseek(fd,0,2);
	int file_size = ftell(fd);
	fseek(fd,0,0);

	char name_snd[sizeof(int)+strlen(path_snd)];
	bzero(name_snd,sizeof(name_snd));
	memcpy(name_snd,&file_size,4);
	memcpy(name_snd+4,path_snd,strlen(path_snd));

	int len = sizeof(struct sockaddr_in);
	int ret = write(c_fd,name_snd,sizeof(name_snd));
	if (ret == -1)
	{
		perror("head send");
		return -1;
	}
	usleep(50000);
	char file_snd[1024] = {0};
	while(1)
	{
		int size = fread(file_snd,1,1024,fd);
		if (size == -1)
		{
			perror("文件读取失败");
			return -1;
		}
		if (size == 0)
		{
			break;
		}
		ret = write(c_fd,file_snd,size);
		if (ret <= 0)
		{
			perror("数据发送失败	");
			return -1;
		}
		bzero(file_snd,1024);
	}
	printf("%s 发送成功！\n", path_snd);


	return 0;
}



void * Msg_Rcv(void * arg)
{
	int ret ;
	char msg_rcv[100] = {0};
	while(1)
	{
		ret = read(c_fd,msg_rcv,100);
		if (ret <= 0)
		{
			perror("msg_rcv");
		}
		if (strncmp(msg_rcv,"HI",2) == 0)
		{
			beep_reset();	//停止报警
		}
		bzero(msg_rcv,100);
	}
}