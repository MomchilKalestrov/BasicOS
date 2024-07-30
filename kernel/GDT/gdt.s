.section .data
	GDT_Start:
		null_descriptor:
		.long 0x0
		.long 0x0
		code_descriptor:
		.word 0xffff
		.word 0x0
		.byte 0x0
		.byte 0b10011010
		.byte 0b11001111
		.byte 0x0
		data_descriptor:
		.word 0xffff
		.word 0x0
		.byte 0x0
		.byte 0b10010010
		.byte 0b11001111
		.byte 0x0
		user_code_descriptor:
		.word 0xffff
		.word 0x0
		.byte 0x0
		.byte 0b11111010
		.byte 0b11001111
		.byte 0x0
		user_data_descriptor:
		.word 0xffff
		.word 0x0
		.byte 0x0
		.byte 0b11110010
		.byte 0b11001111
		.byte 0x0
	GDT_End:

	GDT_Descriptor:
		.word GDT_End - GDT_Start - 1
		.long GDT_Start

	.set CODE_SEG, code_descriptor - GDT_Start
	.set DATA_SEG, data_descriptor - GDT_Start

.section .text
.type _load_gdt, @function
_load_gdt:
	lgdt (GDT_Descriptor) /* Load the GDT */

	ljmp $0x08, $reload_CS 	/* Reload the code segment register */
	reload_CS:

	movw $0x10, %ax /* Reload the data segment registers */
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
    
    ret