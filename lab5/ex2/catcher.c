#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int mode_change_requests = 0;
void handle_signal(int signum, siginfo_t *info, void *context) {
    int mode = info->si_status;
    printf("Mode: %d\n", mode);

    switch (mode) {
        case 1:
            for (int i = 1; i <= 100; ++i) {
                printf("%d ", i);
            }
            printf("\n");
            break;
        case 2:
            mode_change_requests++;
            printf("Mode changes so far: %d\n", mode_change_requests);
            break;
        case 3:
            printf("Exiting...\n");
            break;
    }
    
    sigval_t sigval = {mode};
    int sender_pid = info -> si_pid;
    sigqueue(sender_pid, SIGUSR1, sigval);

    if(mode == 3) exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("My PID: %d\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}
