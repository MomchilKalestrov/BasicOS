#include "lib/terminal/terminal.h"
#include "lib/filesystem/filesystem.h"
#include "lib/memory/memory.h"
#include "bin/programmenu.c"

void kernel_main(void) {
	mmu_init();
	gdt_init();
	terminal_init();
	keyboard_init();
	programmenu_main();
	for(;;);
}
