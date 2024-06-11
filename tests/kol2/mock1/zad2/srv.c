#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define L_SLOW 8

int main(void) {
  int status, gniazdo, dlugosc, gniazdo2, lbajtow, i;
  struct sockaddr_in ser, cli;
  char buf[200];
  char pytanie[L_SLOW] = "abcdefgh";
  char odpowiedz[L_SLOW][10] = {"alfa", "bravo",   "charlie", "delta",
                                "echo", "foxtrot", "golf",    "hotel"};

  gniazdo = socket(AF_INET, SOCK_STREAM, 0);
  if (gniazdo == -1) {
    printf("blad socket\n");
    return 0;
  }

  memset(&ser, 0, sizeof(ser));
  // przypisz gniazdu 'gniazdo' numer portu (np 9000, jesli nie dziala ustal
  // wlasny numer portu) oraz interfejs sieciowy 127.0.0.1, zwroc status
  ser.sin_family = AF_INET;
  ser.sin_port = htons(9000); // Use port 9000, change if necessary
  ser.sin_addr.s_addr = inet_addr("127.0.0.1");
  status = bind(gniazdo, (struct sockaddr *)&ser, sizeof(ser));

  if (status == -1) {
    printf("blad 01\n");
    return 0;
  }

  // utw�rz kolejk� oczekujacych r�wna 10
  status = listen(gniazdo, 10);

  if (status == -1) {
    printf("blad 02\n");
    return 0;
  }
  while (1) {
    dlugosc = sizeof cli;
    // czekaj na przychodzace po�aczenie; gdy przyjdzie przypisz mu 'gniazdo2'
    gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (socklen_t *)&dlugosc);

    if (gniazdo2 == -1) {
      printf("blad 03\n");
      return 0;
    }
    lbajtow = 1;
    while (lbajtow > 0) {
      lbajtow = read(gniazdo2, buf, sizeof buf);
      if (lbajtow > 0) {
        for (i = 0; i < L_SLOW && pytanie[i] != buf[0]; i++)
          ;
        if (i < L_SLOW)
          write(gniazdo2, odpowiedz[i], strlen(odpowiedz[i]));
      }
    }
    close(gniazdo2);
  }
  close(gniazdo);
  printf("KONIEC DZIALANIA SERWERA\n");
  return 0;
}
