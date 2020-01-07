#include "dbConfig.h"

void main(){
    MYSQL fd;
    initMysqlConn(&fd);
    insertSerialData(&fd,"a","123.123");
}