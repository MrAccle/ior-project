#ifndef __SERIALTHREAD_H__
#define __SERIALTHREAD_H__
#include <stdio.h>
#include "../mysqldb/dbConfig.h"

#define CHECKTIME 5
void *serialHeartBeat();
void initSerialThread();
void changeSerialValue(const char *s);
#endif