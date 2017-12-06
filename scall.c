#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
//#include <linux/module.h>
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>
#include <linux/uaccess.h>
//#include <linux/sched/cputime.h>
//#include <linux/time.h>
#include <linux/timekeeping.h>

asmlinkage long sys_det(int pid, long int *n_in_CPU, long int *CPU_time, long int *lifetime){
	struct task_struct *task = NULL;
	long int life;
	task  = pid_task(find_vpid(pid), PIDTYPE_PID);

	if(task == NULL) 
		return -1;
	printk("O pid eh %d\n",task->pid);
	life = ktime_to_timespec(ktime_get_boottime()).tv_nsec - task->start_time;
	if(copy_to_user(n_in_CPU ,&(task->sched_info.pcount),sizeof(long int)))
		return -1;
	if(copy_to_user(CPU_time ,&(task->se.sum_exec_runtime),sizeof(long int)));
		return -1;
	if(copy_to_user(lifetime ,&life,sizeof(long int)));
		return -1;
	printk("Quantidade de vezes que o processo %d passa pela CPU: %ld\n",task->pid ,*n_in_CPU);
	printk("Time CPU: %ld\n",*CPU_time);
	printk("Tempo de vida do processo: %ld s\n", *lifetime);
	return 0;
}
