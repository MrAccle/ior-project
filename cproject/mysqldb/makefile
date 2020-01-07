main : dbMain.o dbConfig.o
	gcc -o main dbMain.o dbConfig.o `mysql_config --cflags --libs`

dbMain.o: dbMain.c dbConfig.h
	gcc -c dbMain.c

dbConfig.o: dbConfig.c dbConfig.h
	gcc -c dbConfig.c 

clean :
	rm dbConfig.o dbMain.o