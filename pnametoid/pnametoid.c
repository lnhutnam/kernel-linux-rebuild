#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/pid.h>

asmlinkage long sys_pnametoid(char* name){
	char *process_name;
    	struct task_struct *task;
	process_name = kmalloc(256, GFP_KERNEL);
	printk("[SYSCALL DEBUG] pnametoid syscall.\n");
	if (process_name == NULL){
		printk("[SYSCALL DEBUG] Failure in allocate for process name.\n");
		return -1;
	}

	if (copy_from_user(process_name, name, 256) != 0) {
		// Free memory for process_name
        	kfree(process_name);
		printk("[SYSCALL DEBUG] Failure in copy from user.\n");
        	return -1;
    	}

	for_each_process(task) {
        	if(strcmp(task->comm, process_name) == 0){
			// Free memory for process_name
    			kfree(process_name);
            		return task_pid_nr(task);
        	}
    	}

	return -1;
}

SYSCALL_DEFINE1(pnametoid, char __user *, name) {
    return sys_pnametoid(name);
}
