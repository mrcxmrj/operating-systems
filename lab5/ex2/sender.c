#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int success = 0;
int received_mode = 0;

void handle_signal(int signum, siginfo_t *info, void *context) {
    success = 1;
    received_mode = info->si_status;
}

void set_sigaction() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);

    sigaction(SIGUSR1, &act, NULL);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Wrong number of arguments!");
        return 1;
    }

    int target_pid = atoi(argv[1]);
    const int mode = atoi(argv[2]);

    set_sigaction();

    sigval_t sigval = {mode};
    sigqueue(target_pid, SIGUSR1, sigval);
    printf("I want mode %d\n", mode);

    while (!success);

    printf("Confirmed changing to mode %d\n", received_mode);

    return 0;
}
