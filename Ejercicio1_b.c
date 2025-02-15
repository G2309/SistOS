#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Proceso Padre Inicial: [PID]: %d\n", getpid());


	fork();
	printf("Primer fork - [PID]: %d\t[PPID]: %d\n",getpid(), getppid()); 

	fork();
	printf("Segundo fork - [PID]: %d\t[PPID]: %d\n",getpid(), getppid()); 

	fork();
	printf("Tercero fork - [PID]: %d\t[PPID]: %d\n",getpid(), getppid()); 

	fork();
	printf("Cuarto fork - [PID]: %d\t[PPID]: %d\n",getpid(), getppid()); 


	return 0;
}
