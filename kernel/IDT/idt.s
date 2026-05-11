.extern exception_handler
.extern irq_timer
.extern irq_readkey
.extern irq_readmouse
.extern irq_coprocessor
.extern irq_primaryATA
.extern irq_secondaryATA
.extern graphics_rectangle
.extern return_value
.extern has_return

.section .data  
.global default_handlers
default_handlers:
    .long irq0
    .long irq1
    .long irq2
    .long irq3
    .long irq4
    .long irq5
    .long irq6
    .long irq7
    .long irq8
    .long irq9
    .long irq10
    .long irq11
    .long irq12
    .long irq13
    .long irq14
    .long irq15
    .long irq16
    .long irq17
    .long irq18
    .long irq19
    .long irq20
    .long irq21
    .long irq22
    .long irq23
    .long irq24
    .long irq25
    .long irq26
    .long irq27
    .long irq28
    .long irq29
    .long irq30
    .long irq31
    .long irq32
    .long irq33
    .long irq34
    .long irq35
    .long irq36
    .long irq37
    .long irq38
    .long irq39 
    .long irq40
    .long irq41
    .long irq42
    .long irq43
    .long irq44
    .long irq45
    .long irq46
    .long irq47


    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc
    .long sysfunc

    .long sysfunc # 80th entry

.section .text

irq0:
    # Division by zero 
    iret
irq1:
    # Single step interrupt. Not important 
    call exception_handler
    iret
irq2:
    # Non maskable interrupt
    movw $0b0000111100000011, (0xB8000)
    call exception_handler
    iret
irq3:
    # Breakpoint. Not important
    movw $0b0000111100000100, (0xB8000)
    call exception_handler
    iret
irq4:
    movw $0b0000111100000101, (0xB8000)
    call exception_handler
    iret
irq5:
    movw $0b0000111100000110, (0xB8000)
    call exception_handler
    iret
irq6:
    movw $0b0000111100000111, (0xB8000)
    call exception_handler
    iret
irq7:
    movw $0b0000111100001000, (0xB8000)
    call exception_handler
    iret
irq8:
    # double fault
    iret
irq9:
    # Coproccessor segment overrun.
    iret
irq10:
    movw $0b0000111100001011, (0xB8000)
    call exception_handler
    iret
irq11:
    movw $0b0000111100001100, (0xB8000)
    call exception_handler
    iret
irq12:
    movw $0b0000111100001101, (0xB8000)
    call exception_handler
    iret
irq13:
    # General Protection Fault. Return and pray for the best
    iret
irq14:
    # Page fault
    iret
irq15:
    movw $0b0000111100010000, (0xB8000)
    call exception_handler
    iret
irq16:
    movw $0b0000111100010001, (0xB8000)
    call exception_handler
    iret
irq17:
    movw $0b0000111100010010, (0xB8000)
    call exception_handler
    iret
irq18:
    movw $0b0000111100010011, (0xB8000)
    call exception_handler
    iret
irq19:
    movw $0b0000111100010100, (0xB8000)
    call exception_handler
    iret
irq20:
    movw $0b0000111100010101, (0xB8000)
    call exception_handler
    iret
irq21:
    movw $0b0000111100010110, (0xB8000)
    call exception_handler
    iret
irq22:
    movw $0b0000111100010111, (0xB8000)
    call exception_handler
    iret
irq23:
    movw $0b0000111100011000, (0xB8000)
    call exception_handler
    iret
irq24:
    movw $0b0000111100011001, (0xB8000)
    call exception_handler
    iret
irq25:
    movw $0b0000111100011010, (0xB8000)
    call exception_handler
    iret
irq26:
    movw $0b0000111100011011, (0xB8000)
    call exception_handler
    iret
irq27:
    movw $0b0000111100011100, (0xB8000)
    call exception_handler
    iret
irq28:
    movw $0b0000111100011101, (0xB8000)
    call exception_handler
    iret
irq29:
    movw $0b0000111100011110, (0xB8000)
    call exception_handler
    iret
irq30:
    movw $0b0000111100011111, (0xB8000)
    call exception_handler
    iret
irq31:
    movw $0b0000111100100000, (0xB8000)
    call exception_handler
    iret

/* ----- PIC Interrupts ----- */
    
irq32: # 0
    pusha
    call irq_timer
    popa
    iret
irq33: # 1
    /* Keyboard */
    call irq_readkey
    iret
irq34: # 2
    movw $0b0000111110001110, (0xB8000)
    iret
irq35: # 3
    movw $0b0000111100001101, (0xB8000)
    iret
irq36: # 4
    movw $0b0000111100001100, (0xB8000)
    iret
irq37: # 5
    movw $0b0000111100001011, (0xB8000)
    iret
irq38: # 6
    movw $0b0000111100001010, (0xB8000)
    iret
irq39: # 7
    movw $0b0000111100001001, (0xB8000)
    iret   
irq40: # 8
    movw $0b0000111100001000, (0xB8000)
    iret
irq41: # 9
    movw $0b0000111100000111, (0xB8000)
    iret
irq42: # 10
    movw $0b0000111100000110, (0xB8000)
    iret
irq43: # 11
    movw $0b0000111100000101, (0xB8000)
    iret
irq44: # 12
    call irq_readmouse
    iret
irq45: # 13
    movw $0b0000111100000011, (0xB8000)
    iret
irq46: # 14
    call irq_primaryATA
    iret
irq47: # 15
    call irq_secondaryATA
    iret

sysfunc:
    pushl %ds               # Save data segment register
    pushl %es               # Save extra segment register
    pushl %fs               # Save FS segment register
    pushl %gs               # Save GS segment register
    pushal                  # Save all general-purpose registers
    pushl %esp              # Push stack pointer

    pushl %ecx              # Push ecx
    pushl %ebx              # Push ebx
    pushl %eax              # Push eax
    call _handle_syscall
    add $12, %esp           # Pop all pushed registers
    
    popl %esp               # Pop stack pointer
    popal                   # Restore all general-purpose registers
    popl %gs                # Restore GS segment register
    popl %fs                # Restore FS segment register
    popl %es                # Restore extra segment register
    popl %ds                # Restore data segment register

    cmpl $1, has_return
    jne .no_return
    movl return_value, %eax
    .no_return:

    iret