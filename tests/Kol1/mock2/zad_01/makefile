zad1: bibl1
	gcc zad1.c -o zad1 -ldl

bibl1:
	gcc -g -c -Wall -fPIC bibl1.c
	gcc -g -shared -fPIC -o libbibl1.so bibl1.o
	gcc -c zad1.c
	gcc -o zad1 -L. -Wl,-rpath,. zad1.o -lbibl1
