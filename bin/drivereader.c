uint8_t buffer[512];
uint32_t sector;

void drivereader_init(void) {
	terminal_setcolor(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[y * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
		}
	}

	terminal_row = 0;
	terminal_column = 0;
	terminal_writestring("Û²±° DRIVE READER °±²ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ²±° SHIFT CTRL ALT °±²Û");
	terminal_row = 7;
	terminal_writestring("        Sector number: \n");
	terminal_writestring("       ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       Û                                                                Û°\n");
	terminal_writestring("       ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ°\n");
	terminal_writestring("        °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
}

void drivereader_render(void) {
    terminal_column = 8;
    terminal_row = 9;
    for(uint16_t i = 0; i < 8; ++i) {
        for(uint16_t j = 0; j < 64; ++j)
            terminal_putchar(buffer[i * 64 + j]);
        terminal_column = 8;
        terminal_row = 10 + i;
    }

    terminal_row = 7;
    terminal_column = 22;
    char *str = "                   ";
    string_convert(str, sector);
    terminal_writestring(str);
    terminal_putchar(' ');
}

void drivereader_main(void) {
    drivereader_init();
    char input;
    for(;;) {
        input = keyboard_readchar();
		if(mod_keys == 0b011 && (input == 'q' || input == 'Q')) // CTRL + ALT + Q to quit the program.
			return;

        if(input >= 0x30 && input <= 0x39)
            sector = sector * 10 + (input - 0x30);
        else if (input == '\b')
            sector /= 10;
        else if (input == '\n') {
            terminal_row = 12;
            terminal_column = 37;
            terminal_writestring("[WAIT]");
            filesystem_readsector(sector, buffer);
        }
        drivereader_render();
    }
}