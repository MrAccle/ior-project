#ifndef __dbconfig_h__
#define __dbconfig_h__
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <time.h>


// MYSQL mysql_handle;//mysql handle
// MYSQL_RES *mysql_res;
// MYSQL_ROW mysql_row;

//初始化Mysql
int initMysqlConn(MYSQL *fd);
//输出Mysql错误
void printMysqlError(MYSQL *fd);
//执行Mysql语句
int queryMysql(MYSQL *fd,const char* sql);
//关闭Mysql
int closeMysql(MYSQL *fd);
//获取Mysql结果集
MYSQL_RES* getQueryResult(MYSQL *fd);
//初始化led
void initLed(MYSQL* fd);
//执行插入数据
int insertSerialData(MYSQL* fd,char* serialId,char* value);

//获取当前字符串时间
char* getStrDate();

//定时更改数据库状态 1
// void *updateSerialSate(char* serialId);
/*
MYSQL_RES * STDCALL mysql_store_result(MYSQL *mysql);
unsigned int STDCALL mysql_num_fields(MYSQL_RES *res);
MYSQL_FIELD * STDCALL mysql_fetch_fields(MYSQL_RES *res);

typedef char **MYSQL_ROW;    
MYSQL_ROW   STDCALL mysql_fetch_row(MYSQL_RES *result);
void STDCALL mysql_free_result(MYSQL_RES *result);

获得结果集中的域的属性：
MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *result)
获得域属性数组：
MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *result)
查询被update、delete、insert等受影响的行：
my_ulonglong mysql_affected_rows(MYSQL *mysql) 
*/
#endif