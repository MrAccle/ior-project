#include "mqtt.h"
MQTTClient client;
int serial_fd_mqtt = -1;
void initMQTT(){
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    MQTTClient_create(&client, MQTT_ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    // MQTTClient_setCallbacks(client, NULL, NULL, msgarrvd, NULL);
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS){
        printf("MQTT init fail, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }else{
        printf("MQTT init success\n");
    }
    // MQTTClient_subscribe(client, TOPIC, QOS);
}

void MQTTsendMsg(char* msg){
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    pubmsg.payload = msg;
    pubmsg.payloadlen = strlen(msg);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    int rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    // printf("Message with delivery token %d delivered\n", token);
    if(token == 1){
        printf("MQTT send msg successful.\n");
    }else{
        printf("MQTT send msg fail,and token is [%d]\n", token);
    }
}

void destroyMQTT(){
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}

#ifdef __CLIENT__
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message){
    int i;
    char* payloadptr;
    // printf("Message arrived\n");
    // printf("     topic: %s\n", topicName);
    // printf("   message: ");
    payloadptr = message->payload;
    if(message->payloadlen == 2){
        char buf[2];
        buf[0]=(*payloadptr++);
        buf[1]=(*payloadptr++);
        printf("get mqtt data:%s\n",buf);
        write(serial_fd_mqtt,buf,2);
    }else{
        printf("get mqtt format error! length is more than 2!\n");
        for(i=0; i<message->payloadlen;i++){
            putchar(*payloadptr++);
        }
        putchar('\n');
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void initListenMQTT(char *clientId,int serial_fd){
    serial_fd_mqtt = serial_fd;
    MQTTClient c;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    // char *CLIENTID_LISTEN = "ymh_listen_2019";
    char *CLIENTID_LISTEN = clientId;
    int rc;
    MQTTClient_create(&c, MQTT_ADDRESS, CLIENTID_LISTEN,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(c, NULL, NULL, msgarrvd, NULL);
    if ((rc = MQTTClient_connect(c, &conn_opts)) != MQTTCLIENT_SUCCESS){
        printf("MQTT init fail, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }else{
        printf("MQTT init success\n");
    }
    MQTTClient_subscribe(c, TOPIC, QOS);
}
#endif
#ifdef __SERVER__
MYSQL mysql_fd;
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message){
    int i;
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = message->payload;
    if(message->payloadlen == 2){
        char buf[2];
        buf[0]=(*payloadptr++);
        buf[1]=(*payloadptr++);
        printf("get mqtt data:%s\n",buf);
        char sql[100];
        sprintf(sql,"UPDATE `led` SET `state`='%c' WHERE (`led`='%c') LIMIT 1",buf[1],buf[0]);
        // printf("%s\n",sql);
        queryMysql(&mysql_fd,sql);
        // write(serial_fd_mqtt,buf,2);
    }else{
        printf("get mqtt format error! length is more than 2!\n");
        for(i=0; i<message->payloadlen;i++){
            putchar(*payloadptr++);
        }
        putchar('\n');
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void initListenMQTT(char *clientId,MYSQL fd){
    //serial_fd_mqtt = serial_fd;
    initMysqlConn(&mysql_fd);
    MQTTClient c;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    // char *CLIENTID_LISTEN = "ymh_listen_2019";
    char *CLIENTID_LISTEN = clientId;
    int rc;
    MQTTClient_create(&c, MQTT_ADDRESS, CLIENTID_LISTEN,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(c, NULL, NULL, msgarrvd, NULL);
    if ((rc = MQTTClient_connect(c, &conn_opts)) != MQTTCLIENT_SUCCESS){
        printf("MQTT init fail, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }else{
        printf("MQTT init success\n");
    }
    MQTTClient_subscribe(c, TOPIC, QOS);
}
#endif

//随机生成字符串
char* getRandomStr(){
    char *buf = (char*) malloc(13);
    buf[0] = 'y';
    buf[1] = 'm';
    buf[2] = 'h';
    buf[3] = ':';
    srand(time(NULL));
    for(int i=4;i<13;i++){
        int flag = rand()%3;
        switch(flag){
            case 0:
                buf[i] = rand()%26 + 'a'; 
                break;
            case 1:
                buf[i] = rand()%26 + 'A'; 
                break;
            case 2:
                buf[i] = rand()%10 + '0'; 
                break;
        }
    }
    return buf;
}

// int main(){
//     initMQTT();
//     // initListenMQTT();
//     MQTTsendMsg("mqtt is connet test!");
//     printf("wait for data\n");
//     char ch = 'a';
//     do
//     {
//         ch = getchar();
//     } while(ch!='Q' && ch != 'q');
//     destroyMQTT();
// }