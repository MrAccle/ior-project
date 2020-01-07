#include "dbConfig.h"

const char *DBCONFIG_HOST = "172.16.100.3";
const char *DBCONFIG_DB_NAME = "cdesinger";
const char *DBCONFIG_USERNAME = "root";
const char *DBCONFIG_PASSWORD = "123";
const unsigned int DBCONFIG_PORT = 3306;


int initMysqlConn(MYSQL *fd){
    if(mysql_init(fd)==NULL){
        printf("mysql_init error\n");
        return -1;
    }
    if((mysql_real_connect(fd,DBCONFIG_HOST,DBCONFIG_USERNAME,DBCONFIG_PASSWORD,DBCONFIG_DB_NAME,0,NULL,0))==NULL){
        printMysqlError(fd);
        return -1;
    }
    return 0;
}

//执行Mysql
int queryMysql(MYSQL *fd,const char* sql){
    if(fd != NULL){
        if(mysql_query(fd,sql) == 0){
            return 0;
        }else{
            printMysqlError(fd);
            return -1;
        }
    }else{
        return -1;
    }
}

//打印Mysql错误
void printMysqlError(MYSQL *fd){
    printf("mysql error->%s\n",mysql_error(fd));
}

//关闭Msql句柄
int closeMysql(MYSQL *fd){
    if(fd != NULL){
        mysql_close(fd);
     }
    return 0;
}

//获取执行结果集
MYSQL_RES* getQueryResult(MYSQL *fd){
    MYSQL_RES* res = mysql_store_result(fd);
    return res;
}

//释放结果集
void freeResult(MYSQL_RES* res){
    if(res != NULL){
        mysql_free_result(res);
    }
}

/* 插入传感器数据 */
int insertSerialData(MYSQL* fd,char* serialId,char* value){
    if(fd == NULL){
        printf("insert serial data error because the fd is null\n");
        return -1;
    }
    char sql[256];
    char *strDate = getStrDate();
    sprintf(sql,"INSERT INTO `value` (`serialId`, `value`, `uploadTime`) VALUES ('%s', '%s', '%s')",serialId,value,strDate);
    printf("the sql is:%s\n",sql);
    //释放所占空间
    free(strDate);
    return queryMysql(fd,sql);    
}
/* 初始化所有的led */
void initLed(MYSQL* fd){
    char *sql ="update led set STAte = 0";
    queryMysql(fd,sql);
    free(sql);
}

/* 获取字符串时间 */
char* getStrDate(){
    time_t t;
    struct tm * lt;
    time (&t);//获取Unix时间戳。    
    lt = localtime(&t);//转为时间结构。    
    char *strDate =(char *)malloc(20*sizeof(char));
    //国区 +8
    sprintf(strDate,"%04d-%02d-%02d %02d:%02d:%02d",1900+lt->tm_year,lt->tm_mon,lt->tm_mday,lt->tm_hour,lt->tm_min,lt->tm_sec);
    return strDate;
}
