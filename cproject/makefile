CC=arm-linux-gnueabi-gcc
TARGET = main server

all: $(TARGET)

main: main.o serial.o lcd.o lcd_var.o netConfig.o mqtt.o
	$(CC) -o clientMain main.o serial.o lcd.o lcd_var.o netConfig.o  mqtt.o -lpthread -l paho-mqtt3c 
	#-I ~/lib/paho.mqtt.c/src -L ~/lib/paho.mqtt.c/build/output -l paho-mqtt3c 
	#-I ~/lib/paho.mqtt.c/src -L ~/lib/paho.mqtt.c/build/output -l paho-mqtt3c -l/hmoe/ymh/lib/paho.mqtt.c/build/output
main.o: main.c ./serial/serial.h ./lcd/lcd.h ./mqtt/mqtt.h 
	$(CC) -c main.c -I ~/lib/paho.mqtt.c/src -L ~/lib/paho.mqtt.c/build/output 

serial.o: ./serial/serial.c 
	$(CC) -c ./serial/serial.c 

lcd.o: ./lcd/lcd.c ./lcd/lcd_var.h 
	$(CC) -c ./lcd/lcd.c 

lcd_var.o: ./lcd/lcd_var.c
	$(CC) -c ./lcd/lcd_var.c

netConfig.o: ./net/netConfig.c 
	$(CC) -c ./net/netConfig.c -D __CLIENT__

mqtt.o: ./mqtt/mqtt.c
	$(CC) -c ./mqtt/mqtt.c -o mqtt.o -I ~/lib/paho.mqtt.c/src -D __CLIENT__


# dbConfig.o: ./mysqldb/dbConfig.c
# 	$(CC) -c ./mysqldb/dbConfig.c
#  `mysql_config --cflags --libs`
server: serverMain.o serialThread.o serverNetConfig.o dbConfig.o serverMqtt.o
	gcc -o server serverMain.o serialThread.o serverNetConfig.o dbConfig.o serverMqtt.o -lpthread `mysql_config --cflags --libs` -l paho-mqtt3c 

serverMain.o: serverMain.c ./thread/serialThread.h
	gcc -c serverMain.c

serialThread.o: ./thread/serialThread.c 
	gcc -c ./thread/serialThread.c

serverNetConfig.o: ./net/netConfig.c 
	gcc -c ./net/netConfig.c -o serverNetConfig.o -D __SERVER__ 

dbConfig.o:./mysqldb/dbConfig.c
	gcc -c ./mysqldb/dbConfig.c

serverMqtt.o: ./mqtt/mqtt.c
	gcc -c ./mqtt/mqtt.c -o serverMqtt.o -D __SERVER__

clean :
	rm *.o