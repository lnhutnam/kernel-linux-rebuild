#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/pid.h>

long sys_pidtoname(int pid, char* buf, int len){
	struct pid* _pid;
    	struct task_struct *task;
	int length;

    	_pid = find_get_pid(pid);
	printk("[SYSCALL DEBUG] pidtoname syscall.\n");
    	if (_pid == NULL){
		printk("[SYSCALL DEBUG] Failue _pid is NULL.\n");
		return -1;
	}

    	task = get_pid_task(_pid, PIDTYPE_PID);

    	if (task == NULL) {
		printk("[SYSCALL DEBUG] Failue task is NULL.\n");
		return -1;
	}

	length = strlen(task->comm);

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

SYSCALL_DEFINE3(pidtoname, int, pid, char __user *, buf, int, len) {
    return sys_pidtoname(pid, buf, len);
}
