#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("./libcollatz.so", RTLD_LAZY);
    if(!handle){
        printf("Error loading library");
    }
    int (*test_collatz_convergence)(int, int) = (int (*)(int, int))dlsym(handle, "test_collatz_convergence");

    int numbers[] = {555, 5555, 55555};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int max_iter = 1000;
    int result;
    for (int i = 0; i < length; i++) {
        result = test_collatz_convergence(numbers[i], max_iter);
        printf("Result: %d", result);
    }

    dlclose(handle);
    return 0;
}