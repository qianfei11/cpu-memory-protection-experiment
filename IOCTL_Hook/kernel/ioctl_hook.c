#include "ioctl_hook.h"

/* assistant functions */
asmlinkage long (*org_ioctl)(const struct pt_regs *pt_regs);
asmlinkage long new_ioctl(const struct pt_regs *pt_regs);
unsigned long **find_sys_call_table(void);
void write_cr0_forced(unsigned long val);
void enable_write_protection(void);
void disable_write_protection(void);

/* system call table */
unsigned long **sys_call_table;

int create_ioctl_hook(void) {
    int rv = 0;

    /* get system call table */
    sys_call_table = (unsigned long **) find_sys_call_table();
    if (sys_call_table == NULL) {
        rv = -ENOMEM;
        printk("failed to get sys_call_table\n");
        goto over;
    }
    printk("sys_call_table = 0x%lx\n", (unsigned long) sys_call_table);

    /* save org syscalls */
    org_ioctl = (void *) sys_call_table[__NR_ioctl];
    printk("org_ioctl = 0x%lx\n", (unsigned long) org_ioctl);

    /* forge syscalls */
    disable_write_protection();
    printk("new_ioctl = 0x%lx\n", (unsigned long) new_ioctl);
    sys_call_table[__NR_ioctl] = (void *) new_ioctl;
    printk("hook SYS_ioctl @ 0x%lx\n", (unsigned long) &sys_call_table[__NR_ioctl]);
    enable_write_protection();

over:
    return rv;
}

void delete_ioctl_hook(void) {

    /* restore syscalls */
    disable_write_protection();
    sys_call_table[__NR_ioctl] = (void *) org_ioctl;
    printk("restore SYS_ioctl\n");
    enable_write_protection();
}

asmlinkage long new_ioctl(const struct pt_regs *pt_regs) {
    //int fd = (int) pt_regs->di;
    int cmd = (int) pt_regs->si;
    void *arg = (void *) pt_regs->dx;
    int val = 87654321;
    int (*func)(void);

    //printk("file descriptor id: %d\n", fd);

    switch (cmd) {
        case IOCTL_ACCESS_USER_MEM:
            val = *(int *) arg;
            printk("read value from userspace => %d\n", val);
            break;
        case IOCTL_EXECUTE_USER_MEM:
            func = arg;
            printk("execute function 0x%lx from userspace\n", (unsigned long) func);
            val = func();
            printk("function return value from userspace => %d\n", val);
            break;
        case IOCTL_COPY_FROM_USER:
            if (copy_from_user(&val, arg, sizeof(int))) {
                printk("error: copy_from_user() failed\n");
                return -EFAULT;
            }
            printk("copy_from_user() => %d\n", val);
            break;
        case IOCTL_COPY_TO_USER:
            if (copy_to_user((int *) arg, &val, sizeof(int))) {
                printk("error: copy_to_user() failed\n");
                return -EFAULT;
            }
            break;
        default:
            return (* org_ioctl)(pt_regs);
    }

    return 0;
}

unsigned long **find_sys_call_table(void) {
    return (unsigned long **) kallsyms_lookup_name("sys_call_table");
}

/* https://github.com/m0nad/Diamorphine/blob/master/diamorphine.c */
/* https://stackoverflow.com/questions/58512430/how-to-write-to-protected-pages-in-the-linux-kernel */
void write_cr0_forced(unsigned long cr0) {
    unsigned long __force_order;
    asm volatile("mov %0,%%cr0" : "+r"(cr0), "+m"(__force_order));
}

/* enable writing sys_call_table */
void enable_write_protection(void) {
    unsigned long cr0 = read_cr0();
    set_bit(16, &cr0);
    write_cr0_forced(cr0);
}

/* disable writing sys_call_table */
void disable_write_protection(void) {
    unsigned long cr0 = read_cr0();
    clear_bit(16, &cr0);
    write_cr0_forced(cr0);
}
