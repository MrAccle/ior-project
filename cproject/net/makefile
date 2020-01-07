F = netMain

main : $(F).o netConfig.o 
	gcc -o $(F) $(F).o netConfig.o dbConfig.o -lpthread `mysql_config --cflags --libs`
	make clean

$(F).o: $(F).c netConfig.h 
	gcc -c $(F).c 

netConfig.o: netConfig.c netConfig.h ../mysqldb/dbConfig.h dbConfig.o
	gcc -c netConfig.c

dbConfig.o: ../mysqldb/dbConfig.c ../mysqldb/dbConfig.h
	gcc -c ../mysqldb/dbConfig.c

clean:
	rm *.o