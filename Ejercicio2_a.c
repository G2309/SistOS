#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double elapsed_time;
    start = clock();
    for (long i = 0; i < 1000000; i++);
    for (long i = 0; i < 1000000; i++);
    for (long i = 0; i < 1000000; i++);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo transcurrido: %f segundos\n", elapsed_time);
    return 0;
}
