#include <linux/linkage.h>	//Syscall espera argumento da pilha
#include <linux/kenel.h>	//Printk
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/sched.h>

extern struct task_struct *find_task_by_vpid(pid_t nr);
EXPORT_SYMBOL(find_task_by_vpid);

asmlinkage long sys_det(int pid){
	struct task_struct *processo = find_task_by_vpid(pid);
	printk("o nr do processo eh %d\n",task_pid_nr(processo));
	return 0;	
}
