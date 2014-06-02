CC = gcc
INCLUDES = -I/usr/local/include/mysql
LIBS = -L/usr/local/lib/mysql -lmysqlclient

all: QUARTA

QUARTA : quarta.c
	gcc -I /usr/include/mysql quarta.c -o QUARTA $(LIBS)


TERCERI : terceri.c
	gcc -I /usr/include/mysql terceri.c -o TERCERI $(LIBS)


SECUNDO : secundo.c
	gcc -I /usr/include/mysql secundo.c -o SECUNDO $(LIBS)
	
clean:
	rm -rf SECUNDO TERCERI