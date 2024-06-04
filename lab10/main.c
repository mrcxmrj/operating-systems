#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define REINDEER_COUNT 9

int returned_reindeers_count = 0;

pthread_mutex_t reindeers_mutexes[REINDEER_COUNT] = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER};

pthread_mutex_t santa_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t santa_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t reindeer_return_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t santa_thread;
pthread_t reindeer_threads[REINDEER_COUNT];

void *reindeer_handler(void *arg) {
  int id = *(int *)arg;

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  pthread_mutex_lock(&reindeers_mutexes[id]);

  while (true) {
    sleep(rand() % 6 + 5);
    pthread_mutex_lock(&reindeer_return_mutex);

    returned_reindeers_count++;
    if (returned_reindeers_count == 9) {
      printf("Renifer: budzę Mikołaja, %d\n", id);
      pthread_cond_signal(&santa_cond);
      returned_reindeers_count = 0;
    }
    pthread_mutex_unlock(&reindeer_return_mutex);
    pthread_mutex_lock(&reindeers_mutexes[id]);

    printf("Renifer%d: jadę na wakacje\n", id);
  }
}

void *santa_thread_handler(void *arg) {
  for (int i = 0; i < 4; i++) {
    pthread_cond_wait(&santa_cond, &santa_mutex);
    printf("Mikołaj: budzę się\n");

    printf("Mikołaj: dostarczam zabawki\n");
    sleep(rand() % 3 + 2);

    for (int j = 0; j < REINDEER_COUNT; j++) {
      pthread_mutex_unlock(&reindeers_mutexes[j]);
    }

    printf("Mikołaj: zasypiam\n");
  }

  for (int j = 0; j < REINDEER_COUNT; j++) {
    pthread_cancel(reindeer_threads[j]);
  }

  return NULL;
}

int main() {
  int reindeer_ids[REINDEER_COUNT];
  pthread_create(&santa_thread, NULL, santa_thread_handler, NULL);

  for (int i = 0; i < REINDEER_COUNT; i++) {
    reindeer_ids[i] = i;
    pthread_create(&reindeer_threads[i], NULL, reindeer_handler,
                   &reindeer_ids[i]);
  }

  pthread_join(santa_thread, NULL);
  for (int i = 0; i < 9; i++) {
    pthread_join(reindeer_threads[i], NULL);
  }

  return 0;
}
