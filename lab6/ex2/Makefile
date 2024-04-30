CC = gcc
CFLAGS = -Wall

all: parent child

parent: parent.c
	$(CC) $(CFLAGS) parent.c -o parent

child: child.c
	$(CC) $(CFLAGS) child.c -o child
	
clean:
	rm -f child parent
