#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include "ioctl_hook.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bealewillmakeit");
MODULE_DESCRIPTION("IOCTL Hook Module");

static int __init hello_init(void) {
    printk("init module\n");

    create_ioctl_hook();

    return 0;
}

static void __exit hello_exit(void) {
    delete_ioctl_hook();

    printk("exit module\n");
}

module_init(hello_init);
module_exit(hello_exit);
