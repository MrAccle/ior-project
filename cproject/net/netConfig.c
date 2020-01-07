#include "netConfig.h"

#ifdef __SERVER__
MYSQL fd;
void initServerListen(){
	printf("is ready to init server listen\n");
	printf("1:init mysql\n");
	initMysqlConn(&fd);
    int server_fd;
	struct sockaddr_in serverAddr,clientAddr;
	int sockaddrSize =sizeof(struct sockaddr_in);
	if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("create socket error:");
		exit(0);
	}
	printf("socket is successful\n");
	bzero(&serverAddr,sockaddrSize);
	//初始化 地址
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	int i = 1;
	setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(int));
	if(bind(server_fd,(struct sockaddr*)&serverAddr,sockaddrSize) != 0){
		perror("bind socket error:");
		exit(0);
	}
	printf("bind is successful\n");
	if(listen(server_fd,MAXLINE) != 0){
		perror("listen socket error:");
		exit(0);
	}
	printf("listen is successful\n");
	printf("init mysql in netConfig\n");
	while(1){
		//初始化变量区域
		pthread_t tid;
		int client_fd = accept(server_fd,(struct sockaddr*)&clientAddr,&sockaddrSize);
		if(client_fd >= 0){
			struct sessionMsg *clientSession=(struct sessionMsg *)malloc(sizeof(struct sessionMsg));
			pthread_t tid;
			inet_ntop(AF_INET,&clientAddr.sin_addr.s_addr,clientSession->ipAddr,16);
			printf("A connection coming and it ip is:%s\n",clientSession->ipAddr);
			clientSession->session_fd=client_fd;
			printf("create thread to handle client\n");
			pthread_create(&tid,NULL,(void *)serverThread,(void*)clientSession);
		}
	}
	close(server_fd);
}

void* serverThread(void *arg){
	printf("server thread strating\n");
	struct sessionMsg *msg=(struct sessionMsg*)arg;
	int client_fd = msg->session_fd;
	char ipAddr[16];
	sprintf(ipAddr,"%s",msg->ipAddr);
	printf("thread is ready to handle client connect:%s\n",ipAddr);
	free(msg);
	while(1){
		char buf[512];
		int count = recv(client_fd,buf,511,0);
		if(count > 0){
			printf("get data:%s\n",buf);
			char *d = strtok(buf,"|");
			if(d != NULL){
				char *serialId = d;
				char *value = strtok(NULL,"|");
				printf("the serial id:%s - value:%s \n",serialId,value);
				insertSerialData(&fd,serialId,value);
				changeSerialValue(serialId);
			}
			memset(buf,0,sizeof(buf));
		}
	}
}
#endif

#ifdef __CLIENT__
int initClientDial(char * SERVER_IPADDR){
	int client_fd;
	struct sockaddr_in serverAddr;
	int sockaddrSize =sizeof(struct sockaddr_in);
	bzero(&serverAddr,sockaddrSize);
	client_fd=socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr=inet_addr(SERVER_IPADDR);
	int ret=connect(client_fd,(struct sockaddr*)&serverAddr,sockaddrSize);
	if(ret >=0){
		printf("connect server successful\n");
		return client_fd;
		// NetSendData(client_fd,"A|1001.1");
	}else{
		printf("connect server error\n");
		return -1;
	}
}
#endif

//发送信息
void NetSendData(int fd,char *data){
	//send(int sockfd, const void *buff, size_t nbytes, int flags);
	if(send(fd,data,strlen(data),0) <= 0){
		perror("send data error: and it return len less zero\n");
	}
}
//关闭连接
void closeNet(int fd){
	if(fd != -1){
		close(fd);
	}
}