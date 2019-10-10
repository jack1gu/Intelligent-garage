#include "head.h"




int pic(char *pic_buf)  //主界面图片处理函数  传入图片名称
{
	int pic_fd = open(pic_buf,O_RDWR);  //打开图片文件 文件为24位bmp 800*480的图片
	if(pic_fd < 0)
	{
		perror("cover bmp open ...");
		return -1;
	}
	char head[54];
	read(pic_fd,head,54);  				//读取头文件数据
	char buf32[480*800*4];
	char buf24[480*800*3];
	read(pic_fd,buf24,480*800*4);  		//读取像素数据
			                                    
	for(int i=0;i<480*800;i++)					 //24位像素转32位像素
	{
		buf32[0+4*i] = buf24[0+3*i];
		buf32[1+4*i] = buf24[1+3*i];
		buf32[2+4*i] = buf24[2+3*i];
		buf32[3+4*i] = 0;

	}
	char buf_fz[480*800*4];
	for(int n=0;n<480;n++)
	{
		for(int m=0;m<800*4;m++)
		{
			buf_fz[(479-n)*800*4+m] = buf32[(0+n)*800*4+m];    //翻转图片
		}
	}
	close(pic_fd);
	int lcd_fd = open("/dev/fb0",O_RDWR);  //打开LCD文件
	if(lcd_fd < 0)
		{
			perror("lcd open ...");
			return -1;
		}

	unsigned char *lcd=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0); //使用虚拟内存

	for(int i=0;i<800*480*4;i++)
		*(lcd+i) = buf_fz[i];
	close(lcd_fd);
	return 0;
}