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
        if(child_pid != 0) { // child_pid == 0 when we're in the child
            printf("Child PID: %d\n", child_pid);
        }
    }

    wait();
    printf("argv[1]: %i", count);
    return 0;
}
