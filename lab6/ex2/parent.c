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
  printf("Range (e.g. 0 1): ");
  scanf("%lf %lf", &start, &end);

  pid_t child_pid = fork();
  if (child_pid == 0) {
    execl("./child", "child", (char *)NULL);
    return -1;
  } else {

    int fd = open(FIFO_PATH, O_WRONLY);

    char buffer[100];
    sprintf(buffer, "%lf %lf", start, end);
    write(fd, buffer, strlen(buffer));
    close(fd);

    fd = open(FIFO_PATH, O_RDONLY);

    double result;
    read(fd, &result, sizeof(result));
    printf("Result: %f\n", result);

    close(fd);

    unlink(FIFO_PATH);
  }

  return 0;
}
