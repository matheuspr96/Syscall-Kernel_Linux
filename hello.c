#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
#include <linux/module.h>
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>
#include <linux/sched/cputime.h>
#include <linux/time.h>
#include <linux/timekeeping.h>

//long int tempo_tarefa = task_sched_runtime(task); // Deu erro ao compilar e o propio compilador recomendou o uso
//long int tempo_CPU = task->se.sum_exec_runtime;   Funciona porem chama função 


asmlinkage long sys_hello(int pid){

	struct task_struct *task = NULL;
	task  = pid_task(find_vpid(pid), PIDTYPE_PID);

	// **Time now** //
	struct timespec real_time;
	real_time = current_kernel_time();
	// 
	// tentativa 2
	/*
	struct timespec time;
	long int t = time.system_time_snapshot.real;
	time = ns_to_timespec(t);
	*/

	struct timespec real;
	getnstimeofday(&real);
	
	
	if(task == NULL) 
		return -1;

	printk("O pid eh %d\n",task->pid);
	printk("Quantidade de vezes que o processo %d passa pela CPU: %ld\n",task->pid ,(unsigned long int)task->sched_info.pcount);
	printk("Time CPU: %ld\n",(unsigned long int)task->se.sum_exec_runtime);

	printk("Tempo inicio processo: %lld\n", task->start_time);
	printk("Tempo atual  with struct: %ld\n",real_time.tv_nsec);
	printk("Tempo atual  with snapshot: %lld\n",ktime_get_real_ns());
	printk("Tempo atual  with gettime: %lld\n",real.tv_nsec);
	
	
	return 0;	
}
