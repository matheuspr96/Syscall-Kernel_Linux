#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
#include <linux/module.h>
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>
#include <linux/sched/cputime.h>
#include <linux/time.h>
#include <linux/timekeeping.h>

asmlinkage long sys_det(int pid){

	struct task_struct *task = NULL;
	task  = pid_task(find_vpid(pid), PIDTYPE_PID);

	if(task == NULL) 
		return -1;
	struct timespec bott;
	getboottime(&bott);

	/*
	printk("O pid eh %d\n",task->pid);
	printk("Quantidade de vezes que o processo %d passa pela CPU: %ld\n",task->pid ,(unsigned long int)task->sched_info.pcount);
	printk("Time CPU: %ld\n",(unsigned long int)task->se.sum_exec_runtime);
*/
	printk("start_time: %lld em segundos\n\n", (task->start_time/1000000000));
	printk("boot_time: %lld em segundos\n\n", bott.tv_sec);
	return 0;	
}
