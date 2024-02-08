echo off
:loop
cls
cd ..
i686-elf-as boot.s -o iso\boot.o
i686-elf-gcc -c kernel.c -o iso\kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o iso\temp.bin -ffreestanding -O2 -nostdlib iso\boot.o iso\kernel.o -lgcc
copy iso\temp.bin iso\boot\basicos.bin
del iso\boot\grub\grub.cfg
del OS.iso
copy toolsnstuff\grub.cfg iso\boot\grub\grub.cfg
copy iso\temp.bin iso\boot\basicos.bin
del iso\temp.bin
del iso\kernel.o
del iso\boot.o
cd toolsnstuff