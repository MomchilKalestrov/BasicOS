/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set VIDEO,    1<<2             /* frame-buffer info */
.set FLAGS,    ALIGN | MEMINFO | VIDEO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.set MODE_TYPE, 0               /* 1 for linear framebuffer, 0 for text mode */
.set WIDTH,     960            /* screen width in pixels */
.set HEIGHT,    720            /* screen height in pixels */
.set DEPTH,     8              /* bits per pixel */


.section .multiboot
    .align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long MODE_TYPE
    .long WIDTH
    .long HEIGHT
    .long DEPTH

#/* Declare constants for the multiboot header. */
#.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
#.set MEMINFO,  1<<1             /* provide memory map */
#.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
#.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
#.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */
#
#.section .multiboot
#.align 4
#.long MAGIC
#.long FLAGS
#.long CHECKSUM


.section .bss
    .align 16
    stack_bottom:
        .skip 0x8000
    stack_top:

.section .data
    .global mb_info
    mb_info:
        .long 0

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp

    mov %ebx, (mb_info)

    call _paging_init
    call _load_gdt
    call _idt_init

    call kernel_main

    cli
    1:
        hlt
        jmp 1b

.size _start, . - _start

.include "./kernel/GDT/gdt.s"
.include "./kernel/IDT/idt.s"