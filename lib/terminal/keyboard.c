												/*    0     1    2    3    4    5    6    7    8     9    10    11    12    13   14    15 */
const unsigned char keyboard_layout[128] =		{	'\0', '\0', '1', '2', '3', '4', '5', '6', '7',  '8', '9',  '0',  '-',  '=', '\b', '\t',
												/*   16    17    18   19   20   21   22   23   24    25   26    27    28    29   30    31 */
													'q',  'w',  'e', 'r', 't', 'y', 'u', 'i', 'o',  'p', '[',  ']',  '\n', ' ', 'a',  's',
												/*   32    33    34   35   36   37   38   39   40    41   42    43    44    45   46    47 */
													'd',  'f',  'g', 'h', 'j', 'k', 'l', ';', '\'', '`', ' ',  '\\', 'z',  'x', 'c',  'v',
												/*   48    49    50   51   52   53   54   55   56    57   58 */
													'b',  'n',  'm', ',', '.', '/', ' ', ' ', ' ',  ' ', ' ' };

													/*    0     1    2    3    4    5    6    7    8     9    10   11   12    13   14    15 */
const unsigned char keyboard_layout_shift[128] =	{	'\0', '\0', '!', '@', '#', '$', '%', '^', '&',  '*', '(', ')', '_',  '+', '\b', '\t',
													/*   16    17    18   19   20   21   22   23   24    25   26   27   28    29   30    31 */
														'Q',  'W',  'E', 'R', 'T', 'Y', 'U', 'I', 'O',  'P', '[', ']', '\n', 254, 'A',  'S',
													/*   32    33    34   35   36   37   38   39   40    41   42   43   44    45   46    47 */
														'D',  'F',  'G', 'H', 'J', 'K', 'L', ':', '\"', '~', ' ', '|', 'Z',  'X', 'C',  'V',
													/*   48    49    50   51   52   53   54   55   56    57   58 */
														'B',  'N',  'M', '<', '>', '?', ' ', ' ', ' ',  ' ', ' ' };

#define MOD_NONE  0
#define MOD_CTRL  (1 << 0)
#define MOD_SHIFT (1 << 1)
#define MOD_ALT   (1 << 2)

uint8_t mod_keys = 0;

void keyboard_init(void) {
	inb(0x60);
}

char keyboard_readchar(void) {
	unsigned char scancode;
	unsigned char character;

	while ((inb(0x64) & 0x01) == 0);
	scancode = inb(0x60);

	size_t past_column;
	size_t past_row;

	switch (scancode) {
		case 0x2a:
		case 0x36:
			mod_keys |= MOD_SHIFT;
			past_column = terminal_column;
			past_row = terminal_row;
			terminal_row = 0;
			terminal_column = 61;
			terminal_setcolor(background, foreground);
			terminal_writestring("SHIFT");
			terminal_column = past_column;
			terminal_row = past_row;
			terminal_setcolor(background, foreground);
		    return '\0';
		case 0xaa:
		case 0xb6:
			mod_keys &= ~MOD_SHIFT;
			past_column = terminal_column;
			past_row = terminal_row;
			terminal_row = 0;
			terminal_column = 61;
			terminal_writestring("SHIFT");
			terminal_column = past_column;
			terminal_row = past_row;
		    return '\0';

		case 0x1d:
			mod_keys |= MOD_CTRL;
			past_column = terminal_column;
			past_row = terminal_row;
			terminal_row = 0;
			terminal_column = 67;
			terminal_setcolor(background, foreground);
			terminal_writestring("CTRL");
			terminal_column = past_column;
			terminal_row = past_row;
			terminal_setcolor(background, foreground);
		    return '\0';
		case 0x9d:
			mod_keys &= ~MOD_CTRL;
			past_column = terminal_column;
			past_row = terminal_row;
			terminal_row = 0;
			terminal_column = 67;
			terminal_writestring("CTRL");
			terminal_column = past_column;
			terminal_row = past_row;
		    return '\0';

		case 0x38:
			mod_keys |= MOD_ALT;
			past_column = terminal_column;
			past_row = terminal_row;
			terminal_row = 0;
			terminal_column = 72;
			terminal_setcolor(background, foreground);
			terminal_writestring("ALT");
			terminal_column = past_column;
			terminal_row = past_row;
			terminal_setcolor(background, foreground);
		    return '\0';
		case 0xb8:
			mod_keys &= ~MOD_ALT;
			past_column = terminal_column;
			past_row = terminal_row;
			terminal_row = 0;
			terminal_column = 72;
			terminal_writestring("ALT");
			terminal_column = past_column;
			terminal_row = past_row;
		    return '\0';

		case 0x48: return 0x18; // up
		case 0x4b: return 0x1b; // left
		case 0x50: return 0x19; // down
		case 0x4D: return 0x1a; // right
	}

	if (scancode & 0x80)
		return '\0';
	if (scancode == 0xe0)
		return '\0';

	if(mod_keys == MOD_SHIFT)
		character = keyboard_layout_shift[scancode];
	else
		character = keyboard_layout[scancode];

	return character;
}

void keyboard_readstring(uint8_t *pointer, size_t length) {
	char character;
	uint16_t counter = 0;

	while ((character = keyboard_readchar()) != '\n' && counter < length) {
		if (character == '\0')
			continue;

		if (character == '\b') {
			if(counter > 0)
				--counter;
			pointer[counter] = '\0';
			terminal_putchar(character);
			continue;
		}

		terminal_putchar(character);
		pointer[counter++] = character;
	}
	pointer[counter] = '\0';
}