#include "./kernel_library/mmu/mmu.h"
#include "./kernel_library/drives/drives.h"
#include "./kernel_library/display/display.h"
#include "./kernel_library/input/mouse.h"

void kernel_main(void) {
	mmu_init();
	graphics_init();
	mouse_init();
    drive_init(&mbr);
	foreground = 0xf5ded3;
	graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
	for(;;);
}