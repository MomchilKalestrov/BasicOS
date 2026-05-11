#ifndef __IDT_H
#define __IDT_H

#include <stdint.h>

#include "../PIC/pic.h"

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
	uint16_t    isr_low;
	uint16_t    kernel_cs;
	uint8_t     reserved;
	uint8_t     attributes;
	uint16_t    isr_high;
} __attribute__((packed)) idt_entry_t;

#endif