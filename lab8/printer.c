#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
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

void initializeSemaphore(int sem_id, int sem_val) {
  union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
  } argument;
  argument.val = sem_val;
  if (semctl(sem_id, 0, SETVAL, argument) < 0) {
    perror("Semaphore initialization failed");
    exit(EXIT_FAILURE);
  }
}

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

void printerProcess(struct PrintJob *jobs, int sem_id, int printer_id) {
  while (1) {
    acquireSemaphore(sem_id);
    if (jobs[printer_id].is_assigned) {
      for (int j = 0; j < TEXT_SIZE; j++) {
        printf("%c", jobs[printer_id].content[j]);
        fflush(stdout);
        sleep(1);
      }
      printf("\n");
      jobs[printer_id].is_assigned = 0;
    }
    releaseSemaphore(sem_id);
  }
}

int main() {
  int shm_id = shmget(SHM_KEY, sizeof(struct PrintJob) * PRINTER_NUMBER,
                      IPC_CREAT | 0666);
  if (shm_id < 0) {
    perror("Shared memory allocation failed");
    exit(EXIT_FAILURE);
  }

  struct PrintJob *jobs = shmat(shm_id, NULL, 0);
  if (jobs == (void *)-1) {
    perror("Shared memory attachment failed");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < PRINTER_NUMBER; i++) {
    jobs[i].is_assigned = 0;
  }

  int sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
  if (sem_id < 0) {
    perror("Semaphore allocation failed");
    exit(EXIT_FAILURE);
  }

  initializeSemaphore(sem_id, 1);

  for (int i = 0; i < PRINTER_NUMBER; i++) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork failed");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      printerProcess(jobs, sem_id, i);
      exit(EXIT_SUCCESS);
    }
  }

  for (int i = 0; i < PRINTER_NUMBER; i++) {
    wait(NULL);
  }

  return 0;
}
