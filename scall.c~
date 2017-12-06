#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
#include <linux/module.h>
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>
#include <linux/sched/cputime.h>
#include <linux/time.h>
#include <linux/timekeeping.h>

asmlinkage long sys_det(int pid){
	struct timespec bott;
	struct task_struct *task = NULL;
	struct system_time_snapshot snap;
	task  = pid_task(find_vpid(pid), PIDTYPE_PID);

	if(task == NULL) 
		return -1;
	
	getboottime(&bott);

	printk("O pid eh %d\n",task->pid);
	printk("Quantidade de vezes que o processo %d passa pela CPU: %ld\n",task->pid ,(unsigned long int)task->sched_info.pcount);
	printk("Time CPU: %ld\n",(unsigned long int)task->se.sum_exec_runtime);
	ktime_get_snapshot(&snap);
	//printk("oq era pra ser a hora atual: %lld\n",snap.real);
	printk("Tempo de vida do processo: %lld s\n",(snap.real - (task->real_start_time+bott.tv_nsec))/1000000000);
	return 0;	
}
