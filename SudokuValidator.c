#include <stdio.h>
#include <omp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int grid[9][9];

// Funcion para validar las filas de la matriz
int validar_F(int grid[9][9]){
	int valid = 1;
	#pragma omp parallel for
	for (int i=0; i<9; i++) {
		int num[10] = {0};
		for (int j=0; j<9; j++) {
			int n = grid[i][j];
			if (num[n]) {
				#pragma omp atomic write
				valid = 0;
			} 
			num[n] = 1;
		}
	}
	return valid;
}
// Funcion para validar las columnas, similar a las filas solo se cambiaron los indices i y j
int validar_C(int grid[9][9]){
	int valid = 1;
	#pragma omp parallel for shared(valid)
	for (int i = 0; i < 9; i++) {
		int num[10] = {0};
		for (int j = 0; j < 9; j++) {
			int n = grid[j][i];
			if (num[n]) {
				#pragma omp atomic write
				valid = 0;
			}
			num[n] = 1;
		}
	}
	return valid;
}


// Funcion para validar los subcuadrantes 3x3
int validar_SC(int grid[9][9]) {
	int valid = 1;

	#pragma omp parallel for collapse(2) shared(valid)
	for (int startRow = 0; startRow < 9; startRow += 3) {
		for (int startCol = 0; startCol < 9; startCol += 3) {
			int num[10] = {0};
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					int n = grid[startRow + i][startCol + j];
					if (num[n]) {
						#pragma omp atomic write
						valid = 0;
					}
					num[n] = 1;
				}
			}
		}
	}

	return valid;
}


int main(int argc, char *argv[]) {
	omp_set_num_threads(4);

	if(argc != 2) {
		printf("Uso: %s <archivo_sudoku>\n", argv[0]);
		return 1;
	}
	// Abrir el archivo de sudoku
	int fd = open(argv[1], O_RDONLY);
	if (fd == 1) {
		perror("Error abriendo el archivo");
			return 1;
	}

	// Obtener el tamaño del archivo
	struct stat sb;
	fstat(fd, &sb);

	// Mapear y luego copiar a memoria el archivo
	char *data = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED){
		perror("Error en nmap");
		close(fd);
		return 1;
	}

	for (int i=0; i<81; i++) {
		grid[i/9][i%9] = data[i] - '0';
	}

	// Cerrar el archivo
	munmap(data, sb.st_size);
	close(fd);

	// Validar usando las funciones de arriba
	int filas_val = validar_F(grid);
	int cols_val = validar_C(grid);
	int cuad_val = validar_SC(grid);

	if (filas_val && cols_val && cuad_val) {
        printf("La solución es válida\n");
    } else {
        printf("La solución NO es válida\n");
    }

	return 0;
}
