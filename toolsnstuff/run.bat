echo off
:loop
cls
cd ..
i686-elf-as boot.s -o iso\boot.o
i686-elf-gcc -c kernel.c -o iso\kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o iso\boot\basicos.bin -ffreestanding -O2 -nostdlib iso\boot.o iso\kernel.o -lgcc
del iso\boot\grub\grub.cfg
copy grub.cfg iso\boot\grub\grub.cfg
del iso\kernel.o
del iso\boot.o
qemu-system-x86_64 -kernel iso/boot/basicos.bin
cd toolsnstuff