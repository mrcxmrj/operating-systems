#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("Received SIGUSR1\n");
}
void check_pending_signals() {
    sigset_t pending_signals;
    sigpending(&pending_signals);
    if (sigismember(&pending_signals, SIGUSR1)) {
        printf("There is a pending SIGUSR1 signal\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }
    char *action = argv[1];

    switch (action[0]) {
        case 'n': // none
            break;
        case 'i': // ignore
            signal(SIGUSR1, SIG_IGN);
            break;
        case 'h': // handle
            signal(SIGUSR1, handle_signal);
            break;
        case 'm': {
                sigset_t mask;
                sigemptyset(&mask);
                sigaddset(&mask, SIGUSR1);
                int block_status = sigprocmask(SIG_BLOCK, &mask, NULL);
                if (block_status == 0)
                    printf("SIGUSR1 blocked\n");
                else
                    printf("Failed to block SIGUSR1\n");
            }
            break;
        default:
            printf("Invalid argument\n");
            return 1;
    }

    printf("Sending SIGUSR1 to myself\n");
    raise(SIGUSR1);

    if (action[0] == 'm') check_pending_signals();

    return 0;
}
