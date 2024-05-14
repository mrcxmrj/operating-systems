CC = gcc
CFLAGS = -Wall

all: user printer

printer: printer.c
	$(CC) $(CFLAGS) printer.c -o printer

user: user.c
	$(CC) $(CFLAGS) user.c -o user

clean:
	rm -f printer user
