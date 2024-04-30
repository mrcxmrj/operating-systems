CC = gcc
CFLAGS = -Wall

timer: timer.c integral
	$(CC) $(CFLAGS) timer.c -o timer

integral: integral.c
	$(CC) $(CFLAGS) integral.c -o integral

clean:
	rm -f integral timer results.txt
