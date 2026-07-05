#include <stdio.h>

int main() {
    int value = 15;

    if (value > 10) {
        printf("Greater than 10\n");
    } else {
        printf("Less or equal to 10\n");
    }

    for (int i = 0; i < 5; i++) {
        printf("Loop: %d\n", i);
    }

    return 0;
}
