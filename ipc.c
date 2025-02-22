#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define SHM_NAME "/mi_memoria_compartida"
#define MEM_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    int shm_fd;
    void *shm_ptr;

    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("Error al crear la memoria compartida");
            exit(EXIT_FAILURE);
        }
        ftruncate(shm_fd, MEM_SIZE);
    }

    shm_ptr = mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("Error en mmap");
        exit(EXIT_FAILURE);
    }

    printf("Memoria compartida mapeada correctamente.\n");
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  
        // Proceso hijo: Leer del pipe y escribir en memoria compartida
        close(pipefd[1]);  // Cerrar escritura

        char buffer;
        int index = 0;
        while (read(pipefd[0], &buffer, 1) > 0 && index < MEM_SIZE - 1) {
            ((char *)shm_ptr)[index++] = buffer;
        }
        ((char *)shm_ptr)[index] = '\0';  // Fin de cadena
        close(pipefd[0]);  // Cerrar lectura

        printf("Proceso hijo: escritura en memoria compartida finalizada.\n");
        exit(EXIT_SUCCESS);
    } else {  
        close(pipefd[0]);  // Cerrar lectura
        for (int i = 1; i <= MEM_SIZE; i++) {
            if (i % n == 0) {
                write(pipefd[1], &x, 1);
            }
        }
        close(pipefd[1]); 
        wait(NULL);

        printf("Contenido de la memoria compartida: %s\n", (char *)shm_ptr);

        // liberar memoria compartida
        munmap(shm_ptr, MEM_SIZE);
        close(shm_fd);
        shm_unlink(SHM_NAME);
    }

    return 0;
}

