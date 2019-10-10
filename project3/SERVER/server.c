#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>


int s_fd,cli_fd;
pthread_t msg_id,file_id;

int percent(int p)
{
	char per[20];
	memset(per,'-',20);
	for (int i = 0; i < p/5; ++i)
	{
		per[i] = '#';
		printf("\033[1A%d%% [%s]\n",p,per);
	}
}

int Socket_Init()
{
	s_fd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in s_addr;
	memset(&s_addr,0,sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8888);
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(s_fd,(struct sockaddr*)&s_addr,sizeof(s_addr));
	if (ret == -1)
	{
		perror("bind");
		return -1;
	}
	ret = listen(s_fd,10);
	if (ret == -1)
	{
		perror("listen");
		return -1;
	}

	struct sockaddr_in cli_addr;
	int cli_len = sizeof(struct sockaddr_in);

	cli_fd = accept(s_fd,(struct sockaddr*)&cli_addr,&cli_len);
	if (cli_fd == -1)
	{
		perror("accept");
		return -1;
	}
	if (cli_fd > 0)
	{
		printf("连接成功！\n");
	}

	return 0;
}

void *Msg_Snd(void * arg)
{
	int ret ;
	char msg_snd[100] = {0};
	while(1)
	{
		scanf("%s",msg_snd);
		ret = write(cli_fd,msg_snd,strlen(msg_snd));
		if (ret <= 0)
		{
			perror("msg_snd");
		}
		bzero(msg_snd,sizeof(msg_snd));
	}
}






void * File_Rcv(void*arg)
{

	int ret;
	char rcv_buf[1024] = {0};
	int size;

	while(1)
	{

		ret = read(cli_fd,rcv_buf,1024);
		if (ret == -1)
		{
			perror("read head");
		}
		memcpy(&size,rcv_buf,4);
		printf("收到的文件大小 ： %d 字节\n", size);
		printf("收到文件的名字 ： %s \n",rcv_buf+4 );

		//拼接文件名
		char path[strlen("./")+strlen(rcv_buf+4)];
		bzero(path,sizeof(path));
		sprintf(path,"./%s",rcv_buf+4);

		FILE * fd = fopen(path,"w+");
		if (fd == NULL)
		{
			perror("fopen");
		}
		int num = 0;
		bzero(rcv_buf,sizeof(rcv_buf));
		sleep(2);
		while(num<size)
		{
			ret = read(cli_fd,rcv_buf,sizeof(rcv_buf));
			if (ret == -1)
			{
				perror("read buf");
			}
			int p = (int )(((float)num/(float)size)*100);
			percent(p);	 //进度条
	//		printf("进度条：\033[1A%d%%\n", p);
			
			fwrite(rcv_buf,1,ret,fd);
			num+=ret;
			bzero(rcv_buf,sizeof(rcv_buf));
		}
		printf("接收完成！\n");
		fclose(fd);

	}


	

}








int main()
{
	Socket_Init();
	sleep(1);
	pthread_create(&msg_id,NULL,Msg_Snd,NULL);
	pthread_create(&file_id,NULL,File_Rcv,NULL);
	while(1);

	close(s_fd);
	close(cli_fd);
	return 0;
}