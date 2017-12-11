#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<errno.h>
int main(){
	printf("Digite um pid: ");
	int x,y;
	long int ncpu, cputime;
	long long int lifetime = 0;
	scanf("%d",&y);
	x = syscall(333, y, &ncpu, &cputime, &lifetime);
	if(x == 0)
		printf("Numero de vezes na CPU: %ld\nTempo do processo na CPU: %ld\nTempo de vida do processo: %lld\n",ncpu, cputime,lifetime);
	else return -1;
}
