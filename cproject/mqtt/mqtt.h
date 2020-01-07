#ifndef __MQTT_H__
#define __MQTT_H__
#include <stdio.h>
// #include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
// #include "/home/ymh/lib/paho.mqtt.c/src/MQTTClient.h"
#include <time.h>
#define MQTT_ADDRESS "ws://172.16.100.4:8083/mqtt"
#define CLIENTID  "ymh_client_2019"
#define TOPIC "ymh:desinger"
#define QOS 1
#define TIMEOUT 10000L

//初始化MQTT 此MQTT作为发送信息所用
void initMQTT();
#ifdef __CLIENT__
void initListenMQTT(char *clientId,int serial_fd);
#endif __CLIENT__

#ifdef __SERVER__
#include "../mysqldb/dbConfig.h"
void initListenMQTT(char *clientId,MYSQL fd);
#endif __SERVER__

//销毁MQTT
void destroyMQTT();
//同步发送信息
void MQTTsendMsg(char* msg);
//异步消息接受回调函数
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
//获取随机字符串，用于做客户端ID 长度12 eg:ymh:339aa7a3
char* getRandomStr();
#endif