#ifndef _HEAD_H_
#define _HEAD_H_ 


#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/select.h>
#include <netdb.h>
#include <sqlite3.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>
#include "jpeglib.h"
#include "yuyv.h"
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int finger_ctrl;     	//触摸屏的控制  0为主界面 1为名字注册 2为充值 3报警 4拍照
int finger_fd;
struct input_event finger; //定义触摸屏
/////////picture//////////////////

int pic(char pic_buf[20]);  //请传图片名称

/////////////////////////////////

///////////rfid定义////////////////

#define DEV_PATH "/dev/ttySAC1"
#define data_block 4

int DATA_WRITE;

int tty_fd;
unsigned char DataReadBuf[16];
unsigned char DataWriteBuf[16];
volatile unsigned int ID;  //volatile 不稳定的
volatile unsigned int ID_cmp;	//用于比较前后ID是否相同
unsigned int ID_SND[4];		//只用作防碰撞跟选择之间连接


int Tty_Init();
int Count_Bcc(char * send_buf,int loop_num);
int PiccRequest(int tty_fd);
int PiccAnticoll(int tty_fd);
int CascSelect(int tty_fd);
int  PiccAuthKey(int tty_fd);
int PiccWrite(int tty_fd);
int PiccRead(int tty_fd);
int Rfid_Write();


/////////////////////////////////

//////////sqlite3///////////////////

typedef struct card_infromation  //卡的信息
{
	char  ID[50];
	char name[50];
	int money;
	pthread_t stop_id,pick_id;
	int count;
	struct card_infromation * next;

}CI,*P_ci;
P_ci Card_Node;

sqlite3 *sq;
int Register;

void Sqlite3_Init();
int ID_Insert(sqlite3 *sq);
int ID_Seek(sqlite3 *sq);
int get_result( void * para, int n_column, char ** column_value, char ** column_name );
int Sqlite3_Free(sqlite3 *sq);
int sqlite3_list_init( void * para, int n_column, char ** column_value, char ** column_name );
int ID_Update(sqlite3 *sq);


///////////////////////////////////



/////////ascii////////////////////

#define MMAP_SIZE     800*480*4
#define MMAP_OFFSET   0
#define LCD_DEV_PATH "/dev/fb0"


int zf_size;   //字符串大小
int num;	   //单个字符的位置

typedef struct show_inf
{
  int lcd_fd;/*文件描述符*/
  int dzk_fd;
  int dzk_offset;/*字符取模文件中的偏移量*/

  int * lcd_mmap;/*映射指针*/
  char* dzk_mmap;

  int dzk_file_size; /*dzk取模文件大小*/
}Show_inf;

Show_inf show_inf;

int Show_Ascii_Init();/*初始化*/
int Show_Ascii_Free();/*释放*/
int Delete_Ascii(int x_zs,int y_zs);
int Show_One_Ascii(int x_zs,int y_zs,char ascii);/*显示一个Ascii*/
int Show_Ascii(int x,int y,char * asciis);   /*显示一串Ascii*/
int Show_Pixel(int x,int y,int color);


///////register注册 //////////////

int Register_Fun(); 


////////////////////////////////

/////////list///////////////////

P_ci head;

//P_ci Node_Init();
P_ci Find_Node(P_ci head);
int  Display_Node(P_ci head);
P_ci Add_Node();
P_ci Create_Node();


//////////////////////////////////
////////parking/////////////////

int Parking;
void * Stop_Fun(void * arg)	;
void * Pick_Fun(void * arg);




////////////////////////////////
////////charge///////////

int Charge_Fun();

////////////////////////////////
/////////Host/////////////////

int Host_Fun();

/////////////////////////////////
////////Camera///////////////////

#define LCD_WIDTH  			800
#define LCD_HEIGHT 			480
#define FB_SIZE				(LCD_WIDTH * LCD_HEIGHT * 4)

static unsigned char g_color_buf[FB_SIZE]={0};


int *mmap_fd;
int lcd_fd;

typedef struct VideoBuffer {
    void   *start;  //映射到用户空间的地址
    size_t  length; //采集到数据的长度
} VideoBuffer1; //存放采集数据的位置


int Camera_Exit;
#define BUFFER_COUNT 4
VideoBuffer1 framebuf[BUFFER_COUNT]; 
int num_camera;


//函数声明
unsigned long file_size_get(const char *pfile_path);
void lcd_close(void);
int show_video_data(unsigned int x,unsigned int y,char *pjpg_buf,unsigned int jpg_buf_size);  
int lcd_draw_jpg(unsigned int x,unsigned int y,const char *pjpg_path);
void lcd_draw_point(unsigned int x,unsigned int y, unsigned int color);
int mmap_lcd(void);
int lcd_open(void);
void *real_time_yuyv(void*arg);
pthread_t camera_pid;
int camera();
int get_picture_flag; //设置拍照变量



/////socket//////////////////

#define SERVER "192.168.2.59"
int c_fd;
int Socket_Init();
int File_Snd(char *path_snd);
pthread_t msg_id;
void * Msg_Rcv(void * arg);

///////////////////////////

////////beep/////////////////

#define ON  0
#define OFF 1

#define  Beep_RD  3
int beep_fd;
int rt;

int beep_init();
void beep_set();
void beep_reset();


/////////////////////

#endif