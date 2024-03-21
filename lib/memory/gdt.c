#define GDT_SIZE 3

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t type;
    uint8_t other;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[GDT_SIZE];
struct gdt_ptr gp;

void gdt_adddescriptor(int index, uint32_t base, uint32_t limit, uint8_t type, uint8_t other) {
    gdt[index].base_low = (base & 0xFFFF);
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = (limit & 0xFFFF);
    gdt[index].other = ((limit >> 16) & 0x0F);

    gdt[index].other |= (other & 0xF0);
    gdt[index].type = type;
}

void gdt_init() {
    gp.limit = (sizeof(struct gdt_entry) * GDT_SIZE) - 1;
    gp.base = (uint32_t)&gdt;

    // Null descriptor
    gdt_adddescriptor(0, 0, 0, 0, 0);

    // Code segment
    gdt_adddescriptor(1, 0, 0xFFFFFFFF, 0b10011010, 0b11001111);

    // Data segment
    gdt_adddescriptor(2, 0, 0xFFFFFFFF, 0b10010010, 0b11001111);

    // load the GDT and fix the register
    asm volatile("lgdt (%0)" : : "r" (&gp));
    asm volatile("mov $0x10, %ax\n\t"
                 "mov %ax, %ds\n\t"
                 "mov %ax, %es\n\t"
                 "mov %ax, %fs\n\t"
                 "mov %ax, %gs\n\t"
                 "mov %ax, %ss\n\t"
                 "ljmp $0x08, $next\n\t"
                 "next: ");
}
