#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
  double params[][2] = {
      {0.001, 1},  {0.01, 2}, {0.005, 3}, {0.005, 4},  {0.02, 1},
      {0.02, 2},   {0.02, 3}, {0.03, 4},  {0.0015, 2}, {0.0015, 3},
      {0.0015, 4}, {0.01, 1}, {0.015, 2}, {0.015, 3},  {0.015, 4},
  };
  int num_params = sizeof(params) / sizeof(params[0]);

  for (int i = 0; i < num_params; i++) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
      char width_param[20];
      char processno_param[20];

      gcvt(params[i][0], 10, width_param);
      gcvt(params[i][1], 10, processno_param);
      execl("./integral", "integral", width_param, processno_param,
            (char *)NULL);
      return -1;
    } else {
      clock_t start = clock();
      int status;
      waitpid(child_pid, &status, 0);
      clock_t end = clock();
      double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

      FILE *fp = fopen("results.txt", "a");
      if (fp == NULL) {
        perror("fopen");
        return -1;
      }

      fprintf(fp, "(%f, %f): %fs\n", params[i][0], params[i][1], cpu_time_used);
    }
  }
  return 0;
}
