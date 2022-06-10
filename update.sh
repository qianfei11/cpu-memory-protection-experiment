#!/bin/bash

cd IOCTL_Hook/ && make && cd ../

cd busybox-1.32.1/_install && cp ../../IOCTL_Hook/kernel/hello.ko . && cp ../../IOCTL_Hook/user/client . && find . | cpio -o --format=newc > ../rootfs.img

