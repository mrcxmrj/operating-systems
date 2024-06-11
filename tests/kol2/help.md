## Kolejki
mq_open - otwiera kolejkę (nazwa musi zaczynać się od "/"!)
mq_close - zamyka kolejkę
mq_unlink - usuwa kolejkę z systemu
mq_getattr - odczytuje parametry kolejki i zapisuje we wskazane miejsce
mq_setattr - ustawia parametry kolejki
mq_send - wysyła komunikat do kolejki
mq_receive - odbiera komunikat z kolejki
mq_notify - rejestruje lub wyrejestrowuje mechanizm powiadomień dla kolejki

## Pamieć współdzielona
shm_open - tworzy współdzielony segment w pamięci
ftruncate - określa rozmiar segmentu (fd jest zwracany przez shm_open)
mmap - dołącza segment do przestrzeni adresowej procesu
munmap - odłącza segment od przestrzeni adresowej procesu
shm_unlink - oznacza odłączony segment do usunięcia

## Wątki
pthread_create - stwórz wątek
pthread_equal - porównaj wątki (wartości typu pthread)
pthread_self - wątek bierze swój identyfikator
pthread_attr_init - inicjalizacja attr; potrzebne gdy korzystamy z pthread_attr 
pthread_attr_destroy - potrzebne do czyszczenia gdy użyliśmy pthread_attr
pthread_join - odczytaj wartość po ukończeniu działania wątku

## Synchronizacja wątków
### Semafory - licznik ile procesów może korzystać
sem_open
sem_post
sem_wait
sem_trywait
sem_getvalue
sem_close
### Mutexy - "binarny semafor"
pthread_mutex_init - inicjalizacja mutexu
pthread_mutex_lock - zajmij mutex
pthread_mutex_trylock
pthread_mutex_timedlock - zajmij, czekaj na odblokowanie jeśli zablokowany przez dany czas
pthread_mutex_unlock - odblokuj mutex

## Sockety
```c
// Setup - taki sam dla klienta i serwera
ser.sin_family = AF_INET;
ser.sin_port = htons(9000);
ser.sin_addr.s_addr = inet_addr("127.0.0.1");

socket(AF_INET, SOCK_STREAM, 0); // tworzy socket
status = bind(gniazdo, (struct sockaddr *)&ser, sizeof(ser)); // binduje socket do adresu
status = listen(gniazdo, 10); // słucha na danym gnieździe na max 10 połączeń w kolejce
status = connect(gniazdo, (struct sockaddr *)&ser, sizeof(ser)); // łączy klienta z serwerem (ustanawia połączenie TCP, więc wykonywane tylko raz)
gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (socklen_t *)&dlugosc); // akceptuje połączenie od klienta

lbajtow = read(gniazdo2, buf, sizeof buf); // czyta lbajtow z gniazda2
write(gniazdo2, odpowiedz[i], strlen(odpowiedz[i])); // pisze do gniazda2
```
