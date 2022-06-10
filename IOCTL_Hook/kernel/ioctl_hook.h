#include <linux/slab.h>
#include <linux/kallsyms.h>

#define __NR_ioctl 16

#define IOCTL_ACCESS_USER_MEM 0xCAFE0001
#define IOCTL_EXECUTE_USER_MEM 0xCAFE0002
#define IOCTL_COPY_FROM_USER 0xCAFE0003
#define IOCTL_COPY_TO_USER 0xCAFE0004

#define IOCTL_ARGP_SIZE 128

int create_ioctl_hook(void);
void delete_ioctl_hook(void);
