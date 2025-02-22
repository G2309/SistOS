#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        for (int i = 1; i <= 4000000; i++) {
            if (i % 1000000 == 0) {
				sleep(1000);
                printf("Hijo: %d\n", i);
            }
        }
        printf("Let's all love Lain\n");
    } else {
        while (1);
    }

    return 0;
}

