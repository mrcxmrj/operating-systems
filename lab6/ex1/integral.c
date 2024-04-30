#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define FUNC(x) (4.0 / (x * x + 1.0))

double calculate_integral(double start, double end, double width) {
  double sum = 0.0;
  double x;
  for (x = start; x < end; x += width) {
    sum += FUNC(x) * width;
  }
  return sum;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Wrong number of arguments!");
    return 1;
  }

  double width = atof(argv[1]);
  int num_processes = atoi(argv[2]);

  double interval = 1.0 / num_processes;

  int pipes[num_processes][2];
  pid_t pid;

  for (int i = 0; i < num_processes; i++) {
    pipe(pipes[i]);
    pid = fork();

    if (pid == 0) {
      close(pipes[i][0]);
      double start = i * interval;
      double end = (i + 1) * interval;
      double result = calculate_integral(start, end, width);
      write(pipes[i][1], &result, sizeof(result));
      close(pipes[i][1]);
      exit(0);
    }
  }

  double total_sum = 0.0;
  for (int i = 0; i < num_processes; i++) {
    close(pipes[i][1]);
    double partial_sum;
    read(pipes[i][0], &partial_sum, sizeof(partial_sum));
    close(pipes[i][0]);
    total_sum += partial_sum;
    wait(NULL);
  }

  printf("Result for (%s, %s) is %f\n", argv[1], argv[2], total_sum);

  return 0;
}
