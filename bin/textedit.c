void textedit_init(void) {
	terminal_setcolor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	terminal_writestring("лВБА TEXT EDITOR АБВлллллллллллллллллллллллллллллллллллллВБА SHIFT CTRL ALT АБВл");
}

void textedit_main(void) {
	textedit_init();
	char character;
	while (1) {
		character = keyboard_readchar();
		if(mod_keys == 0b011 && (character == 'q' || character == 'Q')) // CTRL + ALT + Q to quit the program.
			return;

		switch (character)
		{
			case 0x18: if(terminal_row > 0)		--terminal_row; 	continue;
			case 0x1b: if(terminal_column > 0) 	--terminal_column; 	continue;
			case 0x19: if(terminal_row < 25)	++terminal_row; 	continue;
			case 0x1a: if(terminal_column < 80)	++terminal_column; 	continue;
			case '\0': 												continue;
		}

		terminal_putchar(character);
	}
}