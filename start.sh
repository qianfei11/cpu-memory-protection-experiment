#!/bin/sh

#qemu-system-x86_64 -m 64M -nographic -kernel "./linux-5.4/arch/x86/boot/bzImage" -initrd "./busybox-1.32.1/rootfs.img" -append "root=/dev/ram rw console=ttyS0 nokaslr" -smp cores=2,threads=1 -cpu kvm64 #-s -S
#qemu-system-x86_64 -m 64M -nographic -kernel "./linux-5.4/arch/x86/boot/bzImage" -initrd "./busybox-1.32.1/rootfs.img" -append "root=/dev/ram rw console=ttyS0 nokaslr" -smp cores=2,threads=1 -cpu kvm64,smep #-s -S
#qemu-system-x86_64 -m 64M -nographic -kernel "./linux-5.4/arch/x86/boot/bzImage" -initrd "./busybox-1.32.1/rootfs.img" -append "root=/dev/ram rw console=ttyS0 nokaslr" -smp cores=2,threads=1 -cpu kvm64,smap #-s -S
qemu-system-x86_64 -m 64M -nographic -kernel "./linux-5.4/arch/x86/boot/bzImage" -initrd "./busybox-1.32.1/rootfs.img" -append "root=/dev/ram rw console=ttyS0 nokaslr" -smp cores=2,threads=1 -cpu kvm64,smap,smep #-s -S

