#include "serialThread.h"
//两设备状态信息 均为1则在线 不需要修改
int serialAstate = 0;
int serialBstate = 0;
MYSQL mysql;

void *serialHeartBeat(){
    //5秒后
    printf("init serial heart beat!\n");
    while(1){
        sleep(CHECKTIME);
        if(serialAstate == 0){
            char* sql = "UPDATE `iotdevice` SET `state`='0' WHERE (`name`='A')";
            queryMysql(&mysql,sql);
        }else{
            char* sql = "UPDATE `iotdevice` SET `state`='1' WHERE (`name`='A')";
            queryMysql(&mysql,sql);
            serialAstate = 0;
        }
        if(serialBstate == 0){
            char* sql = "UPDATE `iotdevice` SET `state`='0' WHERE (`name`='B')";
            queryMysql(&mysql,sql);
        }else{
            char* sql = "UPDATE `iotdevice` SET `state`='1' WHERE (`name`='B')";
            queryMysql(&mysql,sql);
            serialBstate = 0;
        }
    }
    
}

void initSerialThread(){
    initMysqlConn(&mysql);
    //update led set state = 0
    char *sql = "update led set state = 0";
    queryMysql(&mysql,sql);
}

void changeSerialValue(const char *s){
    if(s[0] == 'A'){
        serialAstate = 1;
    }else{
        serialBstate = 1;
    }
}