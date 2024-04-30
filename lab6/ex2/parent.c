#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "myfifo"

int main() {
  mkfifo(FIFO_PATH, 0666);

  double start, end;
  printf("Range (ie 0 1): ");
  scanf("%lf %lf", &start, &end);

  int fd = open(FIFO_PATH, O_WRONLY);

  char buffer[100];
  sprintf(buffer, "%lf %lf", start, end);
  write(fd, buffer, strlen(buffer));
  close(fd);

  fd = open(FIFO_PATH, O_RDONLY);

  double result;
  read(fd, &result, sizeof(result));
  printf("Wynik obliczeń: %f\n", result);

  close(fd);

  unlink(FIFO_PATH);

  return 0;
}
