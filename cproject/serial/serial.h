#ifndef __SERIAL_H__
#define __SERIAL_H__
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>

#define SERIAL_BAND B115200
//初始化串口 返回串口返回的fd
int initSerial(char* s);
//改变命令行串口
int cleanConsole();
//关闭串口
void closeSerila(int fd);
#endif