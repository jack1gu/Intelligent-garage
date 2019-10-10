

#定义变量保存gcc,arm-linux-gcc
CC=arm-linux-gcc

T=main

CONFIG=-lpthread -lm -lsqlite3 -L /home/yii/arm-linux-sqlite3/lib/ -I /home/yii/arm-linux-sqlite3/include/ -I./jpeg -L./jpeg -ljpeg -lapi_v4l2_arm1


SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

$(T):$(OBJS)
	$(CC) -o $@ $^  $(CONFIG)

%.o:%.c
	$(CC) -c $< -o $@ $(CONFIG)

clean:
	rm *.o $(TARGET)
