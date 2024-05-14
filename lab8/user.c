#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define PRINTER_NUMBER 3
#define TEXT_SIZE 10
#define SHM_KEY 0x1111
#define SEM_KEY 0x2222

struct PrintJob {
  char content[TEXT_SIZE];
  int is_assigned;
  int client_id;
};

void acquireSemaphore(int sem_id) {
  struct sembuf operations[1] = {{0, -1, 0}};
  if (semop(sem_id, operations, 1) < 0) {
    perror("Semaphore acquisition failed");
    exit(EXIT_FAILURE);
  }
}

void releaseSemaphore(int sem_id) {
  struct sembuf operations[1] = {{0, 1, 0}};
  if (semop(sem_id, operations, 1) < 0) {
    perror("Semaphore release failed");
    exit(EXIT_FAILURE);
  }
}

int main() {

  int client_id = getpid();
  printf("PID: %d\n", client_id);

  int shm_id = shmget(SHM_KEY, sizeof(struct PrintJob) * PRINTER_NUMBER, 0666);
  if (shm_id < 0) {
    perror("Shared memory allocation failed");
    exit(EXIT_FAILURE);
  }

  struct PrintJob *print_jobs = shmat(shm_id, NULL, 0);
  if (print_jobs == (void *)-1) {
    perror("Shared memory attachment failed");
    exit(EXIT_FAILURE);
  }

  int sem_id = semget(SEM_KEY, 1, 0666);
  if (sem_id < 0) {
    perror("Semaphore allocation failed");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
  while (1) {
    struct PrintJob new_print_job;
    for (int i = 0; i < TEXT_SIZE; i++) {
      new_print_job.content[i] = 'a' + rand() % 26;
    }
    new_print_job.client_id = client_id;
    new_print_job.is_assigned = 1;

    acquireSemaphore(sem_id);

    for (int i = 0; i < PRINTER_NUMBER; i++) {
      if (!print_jobs[i].is_assigned) {
        memcpy(&print_jobs[i], &new_print_job, sizeof(struct PrintJob));
        printf("%d: %s\n", client_id, new_print_job.content);
        break;
      }
    }

    releaseSemaphore(sem_id);

    sleep(rand() % 10 + 1);
  }

  return 0;
}
