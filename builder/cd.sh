#!/bin/bash
# Change to the parent directory
cd .. #
# Assemble the boot.s file
i686-elf-as kernel/boot.s -o iso/boot.o #
# Compile the kernel.c file
i686-elf-gcc -c kernel/kernel.c -o iso/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra #
# Link the object files
i686-elf-gcc -T builder/linker.ld -o iso/boot/basicos.bin -ffreestanding -O2 -nostdlib iso/boot.o iso/kernel.o -lgcc #
# Remove the old grub.cfg and copy the new one
rm -f iso/boot/grub/grub.cfg #
cp builder/grub.cfg iso/boot/grub/grub.cfg #
# Clean up object files
rm -f iso/kernel.o iso/boot.o #
# Create the ISO image
grub-mkrescue -o BasicOS.iso iso #
# Print QEMU options (commented out)
# echo "-singlestep -no-reboot -d int"
# echo "-d out_asm 2> qemu_log.txt" -serial mon:stdio 
# Run the ISO with QEMU
qemu-system-i386 -cdrom BasicOS.iso -drive file=~/Downloads/disk.img,format=raw -boot d -no-reboot -m 64m # -d int -monitor stdio #
# Change back to the builder directory
cd builder #