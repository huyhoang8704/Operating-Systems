all: main

CFLAGS= -pthread -fcommon
CC=gcc $(CFLAGS)

main: bkwrk bktask bktpool
	$(CC) -c $(CFLAGS) -o main.o main.c
	$(CC) $(CFLAGS) -o mypool main.o bkwrk.o bktask.o bktpool.o

bkwrk: bkwrk.c bktpool.h
	$(CC) $(CFLAGS) -c -o bkwrk.o bkwrk.c

bktask: bktask.c bktpool.h
	$(CC) $(CFLAGS) -c -o bktask.o bktask.c

bktpool: bktpool.c bktpool.h
	$(CC) $(CFLAGS) -c -o bktpool.o bktpool.c

clean:
	rm *.o
	rm mypool
