#include <stdio.h>

int add(int a, int b, int c) {
    return a + b + c;
}

int main() {
    int result = add(10, 20, 30);

    printf("Result: %d\n", result);

    return 0;
}
