flipper: reverse
	gcc flipper.c -L. -lreverse -o flipper

reverse:
	gcc -g -c reverse.c
	ar rcs libreverse.a reverse.o

clean:
	rm *.o *.a reversed/* flipper pikachu.txt notsure.txt isthisprogramming.txt
