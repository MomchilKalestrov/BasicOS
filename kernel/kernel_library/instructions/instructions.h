#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include <stdint.h>

static inline void halt(void) {
	asm volatile("hlt");
}

static inline uint8_t inb(uint16_t port) {
	uint8_t value;
	asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t value;
	asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

static inline uint32_t inl(uint16_t port) {
	uint32_t value;
	asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

static inline void outb(uint16_t port, uint8_t data) {
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

static inline void outw(uint16_t port, uint16_t data) {
	asm volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

static inline void outl(uint16_t port, uint32_t data) {
	asm volatile("outl %0, %1" : : "a"(data), "Nd"(port));
}

static inline void io_wait(void) {
	outb(0x80, 0);
}

static inline void pushb(uint8_t data) {
	asm volatile("pushb %0" : : "a"(data));
}

static inline void pushw(uint16_t data) {
	asm volatile("pushw %0" : : "a"(data));
}

static inline void pushl(uint32_t data) {
	asm volatile("pushl %0" : : "a"(data));
}

static inline uint8_t popb(void) {
    uint8_t data;
	asm volatile("popb %0" : : "a"(data));
    return data;
}

static inline uint16_t popw(void) {
    uint16_t data;
	asm volatile("popw %0" : : "a"(data));
    return data;
}

static inline uint32_t popl(void) {
    uint32_t data;
	asm volatile("popl %0" : : "a"(data));
    return data;
}

#endif