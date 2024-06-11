
#include "zad2.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void mask()
{
    /*  Zamaskuj sygnał SIGUSR2, tak aby nie docierał on do procesu */

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    check_mask();
}

void process()
{
    fork();
    /*  Stworz nowy process potomny i uruchom w nim program ./check_fork
        W procesie macierzystym:
            1. poczekaj 1 sekundę
            2. wyślij SIGUSR1 do procesu potomnego
            3. poczekaj na zakończenie procesu potomnego */
    pid_t pid;
    pid = fork();
    if(pid != 0) {
        sleep(1);
        kill(pid, SIGUSR1);
        wait(0);
    }
}

int main()
{
    mask();
    process();

    return 0;
}
