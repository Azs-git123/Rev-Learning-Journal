#include <stdio.h>

void greet(char *name) {
    char buffer[32];

    snprintf(buffer, sizeof(buffer), "Hello %s", name);

    printf("%s\n", buffer);
}

int main() {
    greet("Reverse Engineer");

    return 0;
}
