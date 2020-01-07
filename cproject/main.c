#include <stdio.h>
#include "./serial/serial.h"
#include "./lcd/lcd.h"
#include "./mqtt/mqtt.h"
#include "./net/netConfig.h"

#define SERVER_IP "172.16.100.4"
#define SERIAL_NAME "/dev/ttyUSB0"
int serial_fd = -1;
int client_fd = -1;
void main(){
    //初始化LED屏幕
    printf("init the led function\n");
    initLcd();
    //初始化串口通信
    printf("init the serial function\n");
    //默认为USB0
    serial_fd = initSerial(SERIAL_NAME);
    //初始化MQTT 只需要订阅
    printf("init the mqtt listen function\n");
    initListenMQTT("client_mqtt_listen",serial_fd);
    // printf("init the mqtt function\n");
    // initMQTT();
    //初始化 socket
    printf("is ready to listen the serial!\n");
    client_fd = initClientDial(SERVER_IP);
    // insertSerialData(&fd,"a","123.123");
    //循环读取线程
    while(1){
        char buf[512];
        int count = 0;
        //1:串口读
        if((count = read(serial_fd,buf,511))>0){
            printf("data:%s\n",buf);
            if(buf[0] =='A' || buf[0] =='B'){
                //2:发送给服务器
                NetSendData(client_fd,buf);
                //3:更改LCD
                char *d = strtok(buf,"|");
                if(d != NULL){
                    char *serialId = d;
                    char *value = strtok(NULL,"|");;
                    // printf("the serial id:%s - value:%s \n",serialId,value);
                    if(serialId[0] == 'A'){
                        changeValueA(value);
                    }else{
                        changeValueB(value);
                    }
                }
                memset(buf,0,sizeof(buf));
            }
        }
    }
    closeSerila(serial_fd);
    // closeNet(client_fd);
}