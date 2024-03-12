CC = gcc
CFLAGS = -Wall -g

all: countdown

countdown: countdown.c
	$(CC) $(CFLAGS) countdown.c -o countdown
	
.PHONY: clean
clean:
	rm countdown
