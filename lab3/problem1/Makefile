CFLAGS = -Wall -Wextra -pthread
LDFLAGS = -pthread

all: seqlock.c
	gcc $(CFLAGS) seqlock.c -o seqlock $(LDFLAGS)
clean:
	rm -f seqlock
