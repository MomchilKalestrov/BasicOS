typedef enum {
	PLAYER_ONE,
	PLAYER_TWO,
	PLAYER_NONE
} status;

status table[3][3] = {
	{PLAYER_NONE, PLAYER_NONE, PLAYER_NONE},
	{PLAYER_NONE, PLAYER_NONE, PLAYER_NONE},
	{PLAYER_NONE, PLAYER_NONE, PLAYER_NONE}
};
uint8_t x = 0;
uint8_t y = 0;
bool turn = true; 	// true - player 1
					// false - player 2

status game_winner(void) {
	    for (int row = 0; row < 3; row++) { 
        if (table[row][0] == table[row][1] && table[row][1] == table[row][2]) { 
            if (table[row][0] == PLAYER_ONE) 
                return PLAYER_ONE; 
            else if (table[row][0] == PLAYER_TWO) 
                return PLAYER_TWO; 
        } 
    } 
  
    for (int col = 0; col < 3; col++) { 
        if (table[0][col] == table[1][col] && table[1][col] == table[2][col]) { 
            if (table[0][col] == PLAYER_ONE) 
                return PLAYER_ONE; 
  
            else if (table[0][col] == PLAYER_TWO) 
                return PLAYER_TWO; 
        } 
    } 
  
    if (table[0][0] == table[1][1] && table[1][1] == table[2][2]) { 
        if (table[0][0] == PLAYER_ONE)
			return PLAYER_ONE;
        else if (table[0][0] == PLAYER_TWO)
            return PLAYER_TWO; 
    } 
  
    if (table[0][2] == table[1][1] && table[1][1] == table[2][0]) { 
        if (table[0][2] == PLAYER_ONE) 
            return PLAYER_ONE; 
        else if (table[0][2] == PLAYER_TWO) 
            return PLAYER_TWO; 
    }

	return PLAYER_NONE;
}

void game_render(void) {
	for(uint8_t i = 0; i < 3; ++i)
		for(uint8_t j = 0; j < 3; ++j) {
			if(table[j][i] == PLAYER_ONE)
				terminal_setcolor(VGA_COLOR_BLUE, VGA_COLOR_BLUE);
			else if(table[j][i] == PLAYER_TWO)
				terminal_setcolor(VGA_COLOR_RED, VGA_COLOR_RED);
			else
				terminal_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

			terminal_putentryat(' ', terminal_color, i * 3 + 36, j * 3 + 9);
			terminal_putentryat(' ', terminal_color, i * 3 + 37, j * 3 + 10);
			terminal_putentryat(' ', terminal_color, i * 3 + 36, j * 3 + 10);
			terminal_putentryat(' ', terminal_color, i * 3 + 37, j * 3 + 9);
		}
	terminal_setcolor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_LIGHT_GREY);
	terminal_putentryat(' ', terminal_color, y * 3 + 36, x * 3 + 9);
	terminal_putentryat(' ', terminal_color, y * 3 + 37, x * 3 + 10);
	terminal_putentryat(' ', terminal_color, y * 3 + 36, x * 3 + 10);
	terminal_putentryat(' ', terminal_color, y * 3 + 37, x * 3 + 9);
	terminal_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void game_init(void) {
	for(uint8_t i = 0; i < 3; ++i)
		for(uint8_t j = 0; j < 3; ++j)
			table[i][j] = PLAYER_NONE;
	x = 0;
	y = 0;
	turn = true;

    terminal_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	terminal_writestring("Û²±° GAME °±²ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ²±° SHIFT CTRL ALT °±²Û");
	terminal_row = 9;
	terminal_writestring("                                      Û  Û\n");
	terminal_writestring("        ÉÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍ»          Û  Û\n");
	terminal_writestring("        º Arrow ³ Move     º        ÛÛÛÛÛÛÛÛ\n");
	terminal_writestring("        º Enter ³ Mark     º          Û  Û\n");
	terminal_writestring("        º Blue  ³ Player 1 º          Û  Û\n");
	terminal_writestring("        º Red   ³ Player 2 º        ÛÛÛÛÛÛÛÛ\n");
	terminal_writestring("        ÈÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍ¼          Û  Û\n");
	terminal_writestring("                                      Û  Û\n");
}

void game_main(void) {
	reset: ;
	game_init();
	unsigned char character;
	for(;;) {
		game_render();

		character = keyboard_readchar();
		if(mod_keys == 0b011 && (character == 'q' || character == 'Q')) // CTRL + ALT + Q to quit the program.
			return;

		switch(character) {
			case 0x18: if(x > 0) --x; break;
			case 0x1b: if(y > 0) --y; break;
			case 0x19: if(x < 2) ++x; break;
			case 0x1a: if(y < 2) ++y; break;
			case '\n': 
				if(table[x][y] == PLAYER_NONE)
					table[x][y] = turn ? PLAYER_ONE : PLAYER_TWO;
				turn = !turn;
				break;
		}

		terminal_row = 8;
		terminal_column = 34;
		switch (game_winner())
		{
			case PLAYER_ONE:
				terminal_writestring("[ P1  WINS ]");
				keyboard_readchar(); // since readchar doens't capture the break scan code by default, you first get it
				keyboard_readchar(); // and after that you can await the next keypress
				goto reset;
			case PLAYER_TWO:
				terminal_writestring("[ P2  WINS ]");
				keyboard_readchar();
				keyboard_readchar();
				goto reset;
			case PLAYER_NONE: // GCC complains there isn't a case for no winner
				break;
		}
	}
}