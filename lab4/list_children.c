#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 0;

int main(int argc, char **argv) {
    int local = 0;
    pid_t child_pid = fork();
    char *program_name = argv[0];
    printf("My name is %s, I am a ", program_name);

    if (child_pid == 0) {
        printf("child process\n");
        global++;
        local++;

        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
        printf("child's local = %d, child's global = %d\n", local, global);
        
        execl("/bin/ls", "ls", argv[1], NULL);
        fprintf(stderr, "execl failed\n");
        return 1;
    } else {
        printf("parent process\n");
        printf("parent pid = %d, child pid = %d\n", getpid(), child_pid);
        
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child exit code: %d\n", WEXITSTATUS(status));
        } else {
            printf("Something went wrong when exiting child\n");
        }
        
        printf("parent's local = %d, parent's global = %d\n", local, global);
        return 0;
    }
}
