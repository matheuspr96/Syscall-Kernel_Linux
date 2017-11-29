#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
#include <linux/module.h>
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>
#include <linux/sched/cputime.h>

//long int tempo_tarefa = task_sched_runtime(task); // Deu erro ao compilar e o propio compilador recomendou o uso
//long int tempo_CPU = task->se.sum_exec_runtime;   Funciona porem chama função 


asmlinkage long sys_hello(int pid){

	struct task_struct *task = NULL;
	task  = pid_task(find_vpid(pid), PIDTYPE_PID);
	
	if(task == NULL) 
		return -1;

	printk("O pid eh %d\n",task->pid);
	printk("Quantidade de vezes que o processo %d passa pela CPU: %ld\n",task->pid ,(unsigned long int)task->sched_info.pcount);
	printk("Time CPU: %ld\n",(unsigned long int)task->se.sum_exec_runtime);

	printk("Tempo inicio processo: %ld\n", task->start_time);
	
	return 0;	
}
