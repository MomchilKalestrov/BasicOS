#include "lib/terminal/terminal.h"
#include "lib/filesystem/filesystem.h"
#include "bin/programmenu.c"

void kernel_main(void) {
	terminal_init();
	keyboard_init();
	programmenu_main();
	for(;;);
}