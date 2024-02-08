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