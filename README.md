# WHY
Why not? I've always wondered how OS-es work and what better way than making my own.

# HOW TO BUILD
The needed tools are an i686 cross compiler, GNU GRUB and xorriso (you may also need the grub-pc-bin package). We are going to work in the root directory of the OS and building it in '/iso'.

## Building
First, we need to assemble boot.s into boot.o. Since we are working in an enviorment where we don't have any standard library, we need to parse the `-freestanding` argument:

`i686-elf-as boot.s -o iso\boot.o`

The next step is to compile kernel.c into kernel.o. Again, we need to parse the `-ffreestanding -nostdlib`:

`i686-elf-gcc -c kernel.c -o iso\kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra`

Then we link all both the files:

`i686-elf-gcc -T linker.ld -o iso\temp.bin -ffreestanding -O2 -nostdlib iso\boot.o iso\kernel.o -lgcc`

## Making the ISO
## Ways of running the OS
### Using virtual machines
One of the simplest and fastest ways of trying the OS is a virtual machine. VirtualBox is recomended due to it's simplicity of operation.

### Using real hardware
**WARNING!** By using the OS this way you could irreversably damage to your computer. Proceed with caution.

The first thing to do is to burn the ISO file to a flash drive. The best way is to use a program named [Rufus](https://rufus.ie/en/).

When you have burned the iso to your selected flash drive, reboot your PC to the BIOS (you usually need to press F1, F12 or DEL).

**Note**: Since there is no standard BIOS that is used on every motherboard, your experience may vary.

From there, using the arrow keys, you need to find a menu named BOOT, where you will set the flash drive as the first device to boot from.

Navigate to an EXIT menu, save your changes and reboot your computer.
