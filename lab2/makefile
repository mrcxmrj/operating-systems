static:
	gcc -g -c collatz.c
	ar rcs libcollatz.a collatz.o
	
shared:
	gcc -g -fPIC -Wall -c collatz.c
	gcc  -g -shared -Wl,-soname,libcollatz.so.1 -o libdemo.so.1.0.1 collatz.o

clean:
	rm *.a *.o *.out *.so*