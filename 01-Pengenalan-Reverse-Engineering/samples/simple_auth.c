#include <stdio.h>
#include <string.h>

int main() {
    char password[50];

    printf("Masukkan password: ");
    scanf("%49s", password);

    if(strcmp(password, "admin") == 0) {
        printf("Akses Diterima\n");
    } else {
        printf("Akses Ditolak\n");
    }

    return 0;
}
