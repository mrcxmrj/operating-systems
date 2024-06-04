#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define REINDEER_COUNT 9

void *reindeer_handler(void *arg) {
  int *id = (int *)arg;

  while (true) {
    printf("Renifer%d: jadę na wakacje\n", *id);
    sleep(5);
  }
}

int main() {
  pthread_t reindeer_threads[REINDEER_COUNT];
  int reindeer_ids[REINDEER_COUNT];

  for (int i = 0; i < REINDEER_COUNT; i++) {
    reindeer_ids[i] = i;
    printf("%d", reindeer_ids[i]);
    pthread_create(&reindeer_threads[i], NULL, reindeer_handler,
                   &reindeer_ids[i]);
  }
}
