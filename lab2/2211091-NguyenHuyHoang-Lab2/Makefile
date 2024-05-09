CFLAGS = -Wall -Wextra -pthread

all: problem1 sum_serial sum_multi-thread messageTransfer problem4

problem1: problem1.c
	gcc -o $@ $<
sum_serial: sum_serial.c
	gcc -o $@ $<

sum_multi-thread: sum_multi-thread.c
	gcc $(CFLAGS) -o $@ $<

messageTransfer: messageTransfer.c
	gcc $(CFLAGS) -o $@ $<
problem4: problem4.c 
	gcc -o $@ $<



clean:
	rm -f sum_serial sum_multi-thread messageTransfer problem1 problem4