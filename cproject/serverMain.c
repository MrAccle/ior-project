// #include "./mysqldb/dbConfig.h"
#include "./mqtt/mqtt.h"
#include "./net/netConfig.h"
#include "./thread/serialThread.h"

// MYSQL mysql;
void main(){
    //启动监听设备状态子线程
    printf("server init seriale thread!\n");
    initSerialThread();
    pthread_t tid;
    pthread_create(&tid,NULL,(void *)serialHeartBeat,NULL);
    // pthread_join(tid,NULL);
    //启动MQTT服务 服务端没必要进行MQTT服务
    printf("server init mqtt listen!\n");
    initListenMQTT("server_mqtt_listen");
    //启动监听socket
    printf("server init listen socket!\n");
    //进入线程阻塞
    initServerListen();
}