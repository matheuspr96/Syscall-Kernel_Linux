#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>	//task_struct
#include <linux/uaccess.h>	//copy_to_user
#include <linux/timekeeping.h>  //ktime_get_boottime()

asmlinkage long sys_det(int pid, long int *n_in_CPU, long int *CPU_time, long long int *lifetime){
	struct task_struct *task = NULL;		//incialização do ponteiro para a estrutura
	long long int life;				//inicialização do da variavel do tempo de vida
	task  = pid_task(find_vpid(pid), PIDTYPE_PID);	//Captura o ponteiro para task_struct através do pid passado por parâmetro

	if(task == NULL) {				//se a task_struct não existir
		int err = -1;				//variável de retorno caso haja erro
		if(copy_to_user(n_in_CPU ,&err,sizeof(int)))
			return -1;

		if(copy_to_user(lifetime ,&err,sizeof(int)))
			return -1;
		if(copy_to_user(CPU_time ,&err,sizeof(int)))
			return -1;
		return -1;
		//retorna -1 em todas as variáveis de entrada e no retorno da função
	}

	life = ktime_get_boot_ns() - task->start_time;
	//tempo que a maquina está ligada em ns - o momento que o processo foi iniciado contando apartido do boot

	if(copy_to_user(n_in_CPU ,&(task->sched_info.pcount),sizeof(long int)))	//retorna 0 quando copia para o user_space com sucesso
		return -1;

	if(copy_to_user(lifetime ,&life,sizeof(long long int)))//retorna 0 quando copia para o user_space com sucesso
		return -1;
	if(copy_to_user(CPU_time ,&(task->se.sum_exec_runtime),sizeof(long int)))//retorna 0 quando copia para o user_space sem erro
		return -1;		
	//dá o print no dmesg
	printk("O pid eh %d\n",task->pid);
	printk("Quantidade de vezes que o processo passa pela CPU: %ld\n",*n_in_CPU);
	printk("Time CPU: %ld\n",*CPU_time);
	printk("Tempo de vida do processo: %lld s\n", *lifetime);
	return 0;		//retorna 0 caso obtenha sucesso
}
