#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<errno.h>
int main(){
	printf("Digite um pid: ");
	int x,y;
	long int ncpu, cputime;
	long long int lifetime=0;
	scanf("%d",&y);
	x = syscall(333,y,&ncpu,&cputime,&lifetime);
	//printf("%d",errno);
	if(x==0)
		printf("N° de vzs na CPU: %ld\n Time in CPU: %ld\n life time: %lld\n",ncpu, cputime,lifetime);
		//comando para testar o tempo de vida do processo:ps -o etimes= -p "pid"
	else printf("n sei q q rolou");
	return 0;
}
