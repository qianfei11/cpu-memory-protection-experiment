#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#define IOCTL_ACCESS_USER_MEM 0xCAFE0001
#define IOCTL_EXECUTE_USER_MEM 0xCAFE0002
#define IOCTL_COPY_FROM_USER 0xCAFE0003
#define IOCTL_COPY_TO_USER 0xCAFE0004

int func() {
    return 12345678;
}

int main(int argc, char *argv[]) {
    int fd = 0xcafebabe;
    int val = 12345678;
    if (argc == 2) {
        if (strcmp(argv[1], "ACCESS_USER_MEM") == 0) {
            if (ioctl(fd, IOCTL_ACCESS_USER_MEM, &val) != 0) {
                printf("IOCTL_ACCESS_USER_MEM error\n");
                return -1;
            }
        } else if (strcmp(argv[1], "EXECUTE_USER_MEM") == 0) {
            if (ioctl(fd, IOCTL_EXECUTE_USER_MEM, func) != 0) {
                printf("IOCTL_EXECUTE_USER_MEM error\n");
                return -1;
            }
        } else if (strcmp(argv[1], "COPY_FROM_USER") == 0) {
            if (ioctl(fd, IOCTL_COPY_FROM_USER, &val) != 0) {
                printf("IOCTL_COPY_FROM_USER error\n");
                return -1;
            }
        } else if (strcmp(argv[1], "COPY_TO_USER") == 0) {
            if (ioctl(fd, IOCTL_COPY_TO_USER, &val) != 0) {
                printf("IOCTL_COPY_FROM_USER error\n");
                return -1;
            }
            printf("copy_to_user() => %d\n", val);
        } else {
            goto failed;
        }
        return 0;
    }

failed:
    printf("usage: %s [ACCESS_USER_MEM|EXECUTE_USER_MEM|COPY_FROM_USER|COPY_TO_USER]\n", argv[0]);
    return -1;
}
