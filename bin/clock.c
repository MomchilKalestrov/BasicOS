


void clock_render(void) {

}

void clock_init(void) {
	terminal_setcolor(VGA_COLOR_DARK_GREY, VGA_COLOR_LIGHT_RED);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	terminal_writestring("Û²±° CLOCK °±²ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ²±° SHIFT CTRL ALT °±²Û");
	terminal_row = 11;
	terminal_writestring("                                   ÉÍÍËÍÍËÍÍ»\n");
	terminal_writestring("                                   º  º  º  º\n");
	terminal_writestring("                                   ÈÍÍÊÍÍÊÍÍ¼\n");
}

void clock_main(void) {
    clock_init();
	char character;

    for(;;) {
		clock_render();

		character = keyboard_readchar();
		if(mod_keys == 0b011 && (character == 'q' || character == 'Q')) // CTRL + ALT + Q to quit the program.
			return;
    }
}