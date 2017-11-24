#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kernel.h>	//Printk
#include <linux/module.h>
#include <linux/pid.h>		//pid_task(), PIDTYPE_PID
#include <linux/sched.h>

/*Antigo
extern struct task_struct *find_task_by_vpid(pid_t nr);
EXPORT_SYMBOL(find_task_by_vpid);
extern struct task_struct *pid_task(struct pid *pid, enum pid_type);
Antigo//
extern struct task_struct *pid_task(struct pid *pid, enum pid_type);
extern struct task_struct *get_pid_task(struct pid *pid, enum pid_type);
//////agora eu não sei qual das 2, mas o kra do fórum mandou usar a pid_task()
*/
asmlinkage long sys_det(int pid){
	//unsigned long long int exec_time;
	struct task_struct *task = NULL;
	task = pid_task(find_vpid(pid), PIDTYPE_PID);
	//exec_time = task -> cputime_expires.sum_exec_runtime;
	//task -> shed_info.pcount;
	printk("O pid eh %d\nO tempo de CPU eh %lld\n",task->pid,(unsigned long int)(task -> sched_info.pcount));
	//printk("Usando ponteiro %lld\n",task -> cputime_expires->sum_exec_runtime);

/*Antigo
	struct task_struct *processo = find_task_by_vpid(pid);
	printk("o nr do processo eh %d\n",task_pid_nr(processo));
Antigo*/
	return 0;	
}
