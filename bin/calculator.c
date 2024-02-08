int32_t first = 0;
int32_t second = 0;
uint8_t option = 0;

char op_t[4] = {'+', '-', '*', '/'};
uint8_t operand = 0;

int32_t calculator_calculate(void) { // due to my naming convention, there's functions named like this :D
	switch(operand) {
		case 0: return first + second;
		case 1: return first - second;
		case 2: return first * second;
		case 3: return (second != 0) ? first / second : 0;
	}
	return 69;
}

void calculator_render(void) {
	terminal_putentryat(0x10, terminal_color, 32, 10 + option);

	terminal_row = 10;
	terminal_column = 34;
	char str1[19];
	string_convert(str1, first);
	terminal_writestring(str1);
	terminal_putchar(' ');
	
	terminal_row = 11;
	terminal_column = 36;
	terminal_putchar(op_t[operand]);

	terminal_row = 12;
	terminal_column = 34;
	char str2[19];
	string_convert(str2, second);
	terminal_writestring(str2);
	terminal_putchar(' ');

	terminal_row = 15;
	terminal_column = 34;
	terminal_writestring("            ");
	char str3[19];
	string_convert(str3, calculator_calculate());
	terminal_row = 15;
	terminal_column = 34;
	terminal_writestring(str3);
}

void calculator_init(void) {
	first = 0;
	second = 0;
	option = 0;
	operand = 0;

	terminal_setcolor(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_LIGHT_BLUE);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	terminal_writestring("Û²±° CALCULATOR °±²ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ²±° SHIFT CTRL ALT °±²Û");
	terminal_row = 9;
	terminal_writestring("                                 ÉÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
	terminal_writestring("                    First number º            º\n");
	terminal_writestring("                        Operator ÌÍ   ÍÍÍÍÍÍÍÍ¹\n");
	terminal_writestring("                   Second number º            º\n");
	terminal_writestring("                                 ÌÍÍÍÑÍÍÍÍÑÍÍÍ¹\n");
	terminal_writestring("                                 ÌÍÍÍÏÍÍÍÍÏÍÍÍ¹\n");
	terminal_writestring("                          Result º            º\n");
	terminal_writestring("                                 ÈÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
}

void calculator_main(void) {
	calculator_init();
	char character;
	for(;;) {
		calculator_render();

		character = keyboard_readchar();
		if(mod_keys == 0b011 && (character == 'q' || character == 'Q')) // CTRL + ALT + Q to quit the program.
			return;

		switch (character)
		{
			case '\0': continue;
			case 0x18:
				terminal_putentryat(' ', terminal_color, 32, 10 + option);
				if(option > 0)
					--option;
				continue;
			case 0x19:
				terminal_putentryat(' ', terminal_color, 32, 10 + option);
				if(option < 2)
					++option;
				continue;
		}

		switch (option)
		{
			case 0:
				if (character >= 0x30 && character <= 0x39) 		first = first * 10 + (character - 0x30);
				else if (character == 0x1a || character == 0x1b) 	first = -first;
				else if (character == '\b') 						first /= 10;
				continue;
			case 1:
				if(operand > 0 && character == 0x1b)
					--operand;
				else if(operand < 3 && character == 0x1a)
					++operand;
				break;
			case 2:
				if (character >= 0x30 && character <= 0x39) 		second = second * 10 + (character - 0x30);
				else if (character == 0x1a || character == 0x1b) 	second = -second;
				else if (character == '\b') 						second /= 10;
				continue;
		}
	}
}