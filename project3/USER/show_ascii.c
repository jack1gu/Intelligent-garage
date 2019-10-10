#include "head.h"


int Show_Ascii_Init()
{
  	num = 0;
 	show_inf.lcd_fd = open(LCD_DEV_PATH,O_RDWR);
  	if(show_inf.lcd_fd == -1) 
  	{
	    perror("open lcd ...");
	    return -1;
  	}

  	show_inf.lcd_mmap = mmap(NULL,MMAP_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,show_inf.lcd_fd,MMAP_OFFSET);
  	if (show_inf.lcd_mmap == MAP_FAILED) 
  	{

	    perror("mmap lcd ...");
	    return -1;
  	}

  	show_inf.dzk_fd = open("./ascii16.Dzk",O_RDONLY);
  	if(show_inf.dzk_fd == -1)
  	{

	    perror("open dzk ...");
	    return -1;
	}

  	show_inf.dzk_file_size = lseek(show_inf.dzk_fd,0,SEEK_END);  /*计算DZK取模文件的大小*/
  	lseek(show_inf.dzk_fd,0,SEEK_SET);/*读写位置复位*/

  	show_inf.dzk_mmap = mmap(NULL,show_inf.dzk_file_size,PROT_READ,MAP_SHARED,show_inf.dzk_fd,MMAP_OFFSET);
  	if (show_inf.dzk_mmap == NULL) 
  	{

	    perror("mmap dzk ...");
	    return -1;
	}

  	return 0;
}


int Show_Ascii_Free()
{
	close(show_inf.lcd_fd);
	close(show_inf.dzk_fd);
	munmap(show_inf.lcd_mmap,MMAP_SIZE);
	munmap(show_inf.dzk_mmap,show_inf.dzk_file_size);

  	return -1;
}


int Show_Ascii(int x_zs,int y_zs,char *ascii)
{
	zf_size = strlen(ascii);
	if(x_zs+16 >800)
	{
		y_zs+=16;
		x_zs= 0;
	}

	/*计算显示字符在字符文件中的偏移量*/
	for (int i = 0; i < zf_size; ++i)
	{
		show_inf.dzk_offset = ascii[i]*(16*16/8);
		unsigned char *p = show_inf.dzk_mmap+show_inf.dzk_offset;
		int y,x1,x2;
		char  type = 0;
		for(y=0; y<16; y++)
		{
			for(x1=0; x1<2; x1++)
			{
				type = *(p+2*y+x1);

				for(x2=0; x2<8; x2++)
				{
					if(type & (0x80 >> (x2)))
					{
						Show_Pixel(x_zs+i*16+x1*8+x2,y_zs+y,0xff0000);
					}
					else
					{
						Show_Pixel(x_zs+i*16+x1*8+x2,y_zs+y,0xffffff);
					}
				}
			}
		}
	}

  	return 0;
}


int Show_One_Ascii(int x_zs,int y_zs,char ascii)
{
 	if(x_zs+16 >800)
 	{
    	y_zs+=16;
   	 	x_zs= 0;
  	}

  	/*计算显示字符在字符文件中的偏移量*/
  	show_inf.dzk_offset = ascii*(16*16/8);
	unsigned char *p = show_inf.dzk_mmap+show_inf.dzk_offset;
  	int y,x1,x2;
  	char  type = 0;
  	for(y=0; y<16; y++)
  	{
		for(x1=0; x1<2; x1++)
		{
	  		type = *(p+2*y+x1);

	  		for(x2=0; x2<8; x2++)
	  		{
				if(type & (0x80 >> (x2)))
	   			{
	      			Show_Pixel(x_zs+num*16+x1*8+x2,y_zs+y,0xff0000);
				}
				else
				{
					Show_Pixel(x_zs+num*16+x1*8+x2,y_zs+y,0xffffff);
				}
	  		}
		}
  	}

  	return 0;
}

int Delete_Ascii(int x_zs,int y_zs)
{
	if(x_zs+16 >800)
	{
		y_zs+=16;
	    x_zs= 0;
	}

  	/*计算显示字符在字符文件中的偏移量*/

	int y,x1,x2;
	for(y=0; y<16; y++)
	{
	  	for(x1=0; x1<2; x1++)
	  	{
	    	for(x2=0; x2<8; x2++)
	    	{
	       	 	Show_Pixel(x_zs+num*16+x1*8+x2,y_zs+y,0xffffff);       
	   		}
	 	}
	}


  return 0;
}


int Show_Pixel(int x, int y,int color)
{
  	*(show_inf.lcd_mmap + 800*y+x) = color;

  	return -1;
}