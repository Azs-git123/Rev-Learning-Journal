#include <stdio.h>
#include <stdlib.h>

int global_init = 100;
int global_uninit;
const char *message = "Hello Reverse Engineering";

int main() {
    int local_var = 42;
    char *heap_var = malloc(100);

    printf("Alamat fungsi main : %p\n", main);
    printf("Global initialized : %p\n", &global_init);
    printf("Global uninitialized : %p\n", &global_uninit);
    printf("String (.rodata) : %p\n", message);
    printf("Local variable (stack) : %p\n", &local_var);
    printf("Heap variable : %p\n", heap_var);

    free(heap_var);

    return 0;
}
