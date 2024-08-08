#include "./kernel_library/freestanding.h"

uint32_t total_memory;

typedef struct multiboot_memory_map {
    uint32_t size;       // Size of the structure (excluding this field)
    uint64_t addr;       // Base address of the memory region
    uint64_t len;        // Length of the memory region
    uint32_t type;       // Type of the memory region (1 = available RAM, other values = reserved)
} multiboot_memory_map_t;
    
typedef struct {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint8_t color_info[6];
} multiboot_info_t;

extern multiboot_info_t *mb_info;

void graphics_pixel(uint16_t x, uint16_t y, uint32_t pixel);
void graphics_glyph(uint16_t x, uint16_t y, char glyph);
uint32_t graphics_getpixel(uint16_t x, uint16_t y);

#include "./kernel_library/mmu/mmu.h"
#include "./kernel_library/string/string.h"
#include "./kernel_library/instructions/instructions.h"
#include "./kernel_library/input/keyboard.h"
#include "./kernel_library/input/mouse.h"
#include "./kernel_library/drives/drives.h"
#include "./PIC/pic.h"
#include "./kernel_library/display/glib.h"
#include "./kernel_library/loader/loader.h"
#include "./PIC/isr.c"
#include "./IDT/idt.c"
#include "./syscalls/syscall.h"
#include "./userland.c"

mbr_header_t mbr;

void kernel_main(void) {
	mmu_init();
	graphics_init();
	mouse_init();
    drive_init(&mbr);
	foreground = 0xf5ded3;
	graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
	enter_userland();
	for(;;);
}