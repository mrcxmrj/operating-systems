## Biblioteki
static - cały kod łączy się ze źródłowym w czasie linkowania
shared - biblioteka jest linkowana przy odpalaniu programu; musi być obecna przy kompilacji
dll - shared, ale nie jest linkowana przy starcie - tylko gdy jest wywoływana; musi być obecna tylko przy użyciu

### Makefile
```make
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
```
### Useful functions
dlopen - otwórz dll
dlsym - weź symbol z dll
dlclose - zamknij dll

## Pliki
### Useful functions
read
write
close

## Procesy
### Useful functions
getpid
getppid - get parent pid
fork
execl - execute file
wait - czekaj aż proces skończy

## Sygnały
### Useful functions
kill - wyślij sygnał
trap - reakcja na dany sygnał
raise - wyślij do siebie
sigqueue - wyślij z argumentem
signal - przechwytywanie sygnału
sigaction - signal na sterydach
pause - czekaj na sygnał
sleep - czekaj przez dany czas

## Potoki
### Useful functions
pipe(fd) - fd[0] do czytania, fd[1] do pisania
