#include <stdio.h>
#include <omp.h>
// Funcion para validar las filas y columnas de la matriz
int validar_FC(int grid[9][9]){
	#pragma omp parallel for
	for (int i=0; i<9; i++) {
		int num[10] = {0};
		for (int j=0; j<9; j++) {
			int n = grid[i][j];
			if (num[n]) return 0; 
			num[n] = 1;
		}
	}
	return 1;
}
// Funcion para validar los subcuadrantes 3x3
int validar_SC(int grid[9][9]) {
	// En este caso utilice collapse para indicar que se realizara un bucle anidado, para
	// asignar un hilo a una iteracion
	// https://www.openmp.org/spec-html/5.2/openmpsu30.html
	#pragma omp parallel for collapse(2)
	for (int startRow = 0; startRow < 9; startRow +=3) {
		for (int startCol = 0; startCol < 9; startCol += 3) { 
			int num[10] = {0};
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					int n = grid[startRow + i][startCol + j];
					if (num[n]) return 0;
					num[n] = 1;
				}
			}
		}
	}
	return 1;
}

int main() {
	return 0;
}
