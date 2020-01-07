#include "serial.h"

int cleanConsole(){
    int fd_console;
    fd_console = open("/dev/ttySAC1",O_RDONLY); 
    ioctl(fd_console, TIOCCONS); 
    close(fd_console);
}

int initSerial(char* s){
    printf("is ready to open serial:%s\n",s);
    int fd;
    struct termios uart_cfg;  
    fd = open(s,O_RDWR);
    if(fd < 0){
        perror("error for open serial");
        return -1;
    }
    cfmakeraw(&uart_cfg);
	cfsetspeed(&uart_cfg,SERIAL_BAND);	
	uart_cfg.c_cc[VTIME]=0;
	uart_cfg.c_cc[VMIN]=1;
	tcflush(fd,TCIOFLUSH);
	tcsetattr(fd,TCSANOW,&uart_cfg);
    return fd;
}

void closeSerila(int fd){
    if(fd != -1){
        close(fd);
    }
}