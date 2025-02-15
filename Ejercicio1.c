#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Proceso Padre inicial [PID]: %d\n", getpid());

	for(int i=0; i < 4; i++) {
		fork();
		printf("Iteracion: %d - [PID]: %d\n[PPID]:%d\n",i,getpid(),getppid());
	} 
	sleep(1);
	return 0;
}
