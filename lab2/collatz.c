#include "collatz.h"

int collatz_conjecture(int input) {
    if(input / 2)
        return input / 2;
    else
        return 3 * input + 1;
}

int test_collatz_convergence(int input, int max_iter) {
    int i = 0;
    while ( i<max_iter && input != 1 ) {
        input = collatz_conjecture(input);
        i++;
    }
    return i;
}