#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	FILE *origen, *destino;
	char buf;

	if (argc != 3) {
		printf("Error: se debe proporcionar un archivo de origen y uno de destino");
		return 1;
	}
	origen = fopen(argv[1], "r");
	if (origen == NULL) {
		printf("No se pudo abrir el archivo de origen");
		return 1;
	} 
	destino = fopen(argv[2], "w");
	if (origen == NULL) {
		printf("Error al abrir un archivo destino");
		fclose(origen);
		return 1;
	}
	while ((buf = fgetc(origen)) != EOF) {
		fputc(buf, destino);
	}

	fclose(origen);
	fclose(destino);
	
	return 0;
}
