#ifndef __netConfg_h__
#define __netConfg_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "../mysqldb/dbConfig.h"

#define MAXLINE 20
#define SERVER_PORT 1973

struct sessionMsg{
    int session_fd;
    char ipAddr[16];
};

void initServerListen();

//初始化客户端连接服务器，返回FD

int initClientDial(char * SERVER_IPADDR);

void *serverThread(void *msg);
void NetSendData(int fd,char *data);
//关闭客户端
void closeNet(int fd);
#endif