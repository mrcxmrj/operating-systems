#include <stdio.h>
#include "collatz.h"

int main() {
    int numbers[] = {555, 5555, 55555};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int max_iter = 1000;
    int result;
    for (int i = 0; i < length; i++) {
        result = test_collatz_convergence(numbers[i], max_iter);
        printf("Result: %d", result);
    }

    return 0;
}