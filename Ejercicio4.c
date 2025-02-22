#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Proceso hijo
        printf("Let's all love Lain\n");
    } else {
        // Proceso padre
        while (1);
    }
    return 0;
}

