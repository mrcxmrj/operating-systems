all: static shared test

object:
	gcc -c collatz.c
	gcc -c test.c
	gcc test.o collatz.o -o test
	gcc test.c

static:
	gcc -g -c collatz.c
	ar rcs libcollatz.a collatz.o
	gcc test.c -L. -lcollatz -o test
	
shared:
	gcc -g -c -Wall -fPIC collatz.c
	gcc -g -shared -fPIC -o libcollatz.so collatz.o	
	gcc -c test.c
	gcc -o test -L. -Wl,-rpath,. test.o -lcollatz

dll: shared
	gcc test_dynamic.c -o test -ldl

clean:
	rm *.a *.o *.out *.so* test