#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/pid.h>

asmlinkage long sys_pidtoname(int pid, char* buf, int len){
	printk("[SYSCALL DEBUG] pidtoname syscall.\n");
	struct pid* _pid;
    	struct task_struct *task;
    	_pid = find_get_pid(pid);

    	if (_pid == NULL){
		printk("[SYSCALL DEBUG] Failue _pid is NULL.\n");
		return -1;
	}

    	task = get_pid_task(_pid, PIDTYPE_PID);

    	if (task == NULL) {
		printk("[SYSCALL DEBUG] Failue task is NULL.\n");
		return -1;
	}

	int length = strlen(task->comm);

	if (length > len - 1) {
		printk("[SYSCALL DEBUG] Exception lenght of task > len input.\n");
		return 0;
	}

    	if (copy_to_user(buf, task->comm, length + 1) != 0) {
		printk("[SYSCALL DEBUG] Failure in copy from user.\n");
        	return -1;
	}

	return length;
}
