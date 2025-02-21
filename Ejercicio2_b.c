#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    clock_t start, end;
    double elapsed_time;

    start = clock();
    pid1 = fork();

    if (pid1 == 0) {
        pid2 = fork();

        if (pid2 == 0) {
            pid3 = fork();

            if (pid3 == 0) {
                for (long i = 0; i < 1000000; i++) {
                    printf("Bisnieto - Iteración: %ld\n", i);
                }
            } else {
                wait(NULL);
                for (long i = 0; i < 1000000; i++) {
                    printf("Nieto - Iteración: %ld\n", i);
                }
            }
        } else {
            wait(NULL);
            for (long i = 0; i < 1000000; i++) {
                printf("Hijo - Iteración: %ld\n", i);
            }
        }
    } else {
        wait(NULL);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido: %f segundos\n", elapsed_time);
    }

    return 0;
}

