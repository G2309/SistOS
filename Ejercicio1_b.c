#include <stdio.h>
#include <unistd.h>

int main() {
	int f = (int)fork();
	if (f == 0) {
		execl("./Ejercicio1_a", (char*)NULL);
	} else {
		printf("%d\n", (int)getpid());
		execl("./Ejercicio1_a", (char*)NULL);
	}

	return(0);
}
