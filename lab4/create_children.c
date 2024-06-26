#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char* argv[]) {
    int count = atoi(argv[1]);
    for (int i=0; i<count; i++) {
        pid_t child_pid;
        child_pid = fork();
        if(child_pid == 0) {
            printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
            return 0;
        }
    }

    for (int i=0; i<count; i++) {
        wait(NULL);
    }
    printf("argv[1]: %d", count);
    return 0;
}
