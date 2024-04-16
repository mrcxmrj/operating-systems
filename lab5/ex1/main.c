#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("test\n");
}

int main() {
    /* printf("PID: %d", getpid()); */
    /* handle_signal(1); */
    signal(SIGINT, handle_signal);
    while (1) {
        sleep(100);
    }
    return 0;
}
