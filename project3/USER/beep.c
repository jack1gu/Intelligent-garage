#include "head.h"


int beep_init()
{
	beep_fd = open("/dev/beep", O_RDWR);
	
	if(beep_fd == -1)
	{
		perror("open:");
		exit(0);
	} 
	return 0;
}

void beep_set()
{
	ioctl(beep_fd,ON,1);
}

void beep_reset()
{
	ioctl(beep_fd,OFF,1);
}