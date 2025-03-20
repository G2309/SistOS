#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdbool.h> 

// Arreglo global para el grid del sudoku 
int grid[9][9];
int cols_val = 0; // Variable global para almacenar el resultado de la validación de columnas

// Función para validar las filas de la matriz
int validar_F(int grid[9][9]) {
    omp_set_nested(1);
    omp_set_num_threads(9);
    
    int valid = 1;
    
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < 9; i++) {
        printf("Validando fila %d con thread ID: %ld\n", i, syscall(SYS_gettid));
        int num[10] = {0};
        for (int j = 0; j < 9; j++) {
            int n = grid[i][j];
            if (n < 1 || n > 9 || num[n]) {
                #pragma omp atomic write // Use el atomic write para evitar race conditions
                valid = 0;
            }
            if (n >= 1 && n <= 9) {
                num[n] = 1;
            }
        }
    }
    return valid;
}

// Función para validar las columnas
int validar_C(int grid[9][9]) {
    omp_set_nested(1); 
    omp_set_num_threads(9);
    
    int valid = 1;
    
    #pragma omp parallel for shared(valid)
    for (int i = 0; i < 9; i++) {
        printf("Validando columna %d con thread ID: %ld\n", i, syscall(SYS_gettid));
        int num[10] = {0};
        for (int j = 0; j < 9; j++) {
            int n = grid[j][i];
            if (n < 1 || n > 9 || num[n]) {
                #pragma omp atomic write
                valid = 0;
            }
            if (n >= 1 && n <= 9) {
                num[n] = 1;
            }
        }
    }
    return valid;
}

// Función para validar los subcuadrantes 3x3
int validar_SC(int grid[9][9]) {
    omp_set_nested(1); 
    omp_set_num_threads(9); 
    
    int valid = 1;
    
    #pragma omp parallel for collapse(2) schedule(dynamic) shared(valid)
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            printf("Validando subcuadrante (%d,%d) con thread ID: %ld\n", 
                   startRow/3, startCol/3, syscall(SYS_gettid));
            int num[10] = {0}; // Arreglo local para cada thread
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int n = grid[startRow + i][startCol + j];
                    if (n < 1 || n > 9 || num[n]) {
                        #pragma omp atomic write
                        valid = 0;
                    }
                    if (n >= 1 && n <= 9) {
                        num[n] = 1;
                    }
                }
            }
        }
    }
    return valid;
}

// Función para el thread que valida columnas
void* thread_validar_columnas(void* arg) {
    printf("Thread de validación de columnas en ejecución. Thread ID: %ld\n", syscall(SYS_gettid));
    cols_val = validar_C(grid);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    // OpenMP para usar solo 1 thread inicialmente
    omp_set_num_threads(1);
    
    if (argc != 2) {
        printf("Uso: %s <archivo_sudoku>\n", argv[0]);
        return 1;
    }

    // Abrir el archivo de sudoku
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error abriendo el archivo");
        return 1;
    }

    // Obtener el tamaño del archivo
    struct stat sb;
    fstat(fd, &sb);

    // Mapear y luego copiar a memoria el archivo
    char *data = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("Error en mmap");
        close(fd);
        return 1;
    }

    for (int i = 0; i < 81; i++) {
        grid[i/9][i%9] = data[i] - '0';
    }

    // Cerrar el archivo
    munmap(data, sb.st_size);
    close(fd);

    // Validar subcuadrantes 3x3
    printf("Iniciando validación de subcuadrantes...\n");
    int cuad_val = validar_SC(grid);
    printf("Resultado de validación de subcuadrantes: %s\n", cuad_val ? "Válido" : "No válido");
    
    // Obtener el PID del proceso padre
    pid_t parent_pid = getpid();
    printf("PID del proceso padre: %d\n", parent_pid);
    
    // Crear un proceso hijo para ejecutar ps
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Error en fork");
        return 1;
    } else if (pid == 0) {
        // Proceso hijo
        char pid_str[20];
        sprintf(pid_str, "%d", parent_pid);
        printf("\n=== PS DURANTE VALIDACIÓN DE COLUMNAS ===\n");
        execlp("ps", "ps", "-p", pid_str, "-lLf", NULL);
        // Si execlp falla
        perror("Error en execlp");
        exit(1);
    } else {
        // Proceso padre
        // Crear un pthread para validar columnas
        pthread_t thread;
        if (pthread_create(&thread, NULL, thread_validar_columnas, NULL) != 0) {
            perror("Error al crear el thread");
            return 1;
        }
        
        // Esperar a que termine el thread
        if (pthread_join(thread, NULL) != 0) {
            perror("Error en pthread_join");
            return 1;
        }
        printf("Resultado de validación de columnas: %s\n", cols_val ? "Válido" : "No válido");
        
        // Mostrar el ID del thread en ejecución
        printf("Thread principal en ejecución. Thread ID: %ld\n", syscall(SYS_gettid));
        
        // Esperar a que termine el hijo que ejecuta ps
        wait(NULL);
        
        // Validar filas
        printf("Iniciando validación de filas...\n");
        int filas_val = validar_F(grid);
        printf("Resultado de validación de filas: %s\n", filas_val ? "Válido" : "No válido");
        
        // Verificar si la solución es válida
        if (filas_val && cols_val && cuad_val) {
            printf("La solución es válida\n");
        } else {
            printf("La solución NO es válida\n");
            printf("Validación de filas: %s\n", filas_val ? "OK" : "Fallo");
            printf("Validación de columnas: %s\n", cols_val ? "OK" : "Fallo");
            printf("Validación de subcuadrantes: %s\n", cuad_val ? "OK" : "Fallo");
        }
        
        // Crear un nuevo proceso hijo para ejecutar ps nuevamente
        pid_t new_pid = fork();
        
        if (new_pid < 0) {
            perror("Error en el segundo fork");
            return 1;
        } else if (new_pid == 0) {
            // Nuevo proceso hijo
            char pid_str[20];
            sprintf(pid_str, "%d", parent_pid);
            printf("\n=== PS ANTES DE TERMINAR EL PROGRAMA ===\n");
            execlp("ps", "ps", "-p", pid_str, "-lLf", NULL);
            // Si execlp falla
            perror("Error en execlp");
            exit(1);
        } else {
            // Esperar al hijo y terminar
            wait(NULL);
            return 0;
        }
    }
}
