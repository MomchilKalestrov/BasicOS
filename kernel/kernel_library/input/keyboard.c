#include "./keyboard.h"

char kb_queue[KB_RING_SIZE];

const unsigned char keyboard_layout[128] =		{	'\0', '\0', '1', '2', '3', '4', '5', '6', '7',  '8', '9',  '0',  '-',  '=', '\b', '\t',
													'q',  'w',  'e', 'r', 't', 'y', 'u', 'i', 'o',  'p', '[',  ']',  '\n', ' ', 'a',  's',
													'd',  'f',  'g', 'h', 'j', 'k', 'l', ';', '\'', '`', ' ',  '\\', 'z',  'x', 'c',  'v',
													'b',  'n',  'm', ',', '.', '/', ' ', ' ', ' ',  ' ', ' ' };

const unsigned char keyboard_layout_shift[128] =	{	'\0', '\0', '!', '@', '#', '$', '%', '^', '&',  '*', '(', ')', '_',  '+', '\b', '\t',
														'Q',  'W',  'E', 'R', 'T', 'Y', 'U', 'I', 'O',  'P', '[', ']', '\n', 254, 'A',  'S',
														'D',  'F',  'G', 'H', 'J', 'K', 'L', ':', '\"', '~', ' ', '|', 'Z',  'X', 'C',  'V',
														'B',  'N',  'M', '<', '>', '?', ' ', ' ', ' ',  ' ', ' ' };

uint8_t _kb_internal_ptr;
uint8_t kb_index;

uint8_t mod_keys = 0;

char _keyboard_readchar(void) {
    for(;;) {
        if(kb_index == _kb_internal_ptr || kb_queue[kb_index] == '\0')
            continue;
        break;
    }

	for(uint8_t i = 0; i < KB_RING_SIZE; i++)
		graphics_glyph(0xfff0, 0xfff0, kb_queue[i]);

    char c = kb_queue[kb_index];
    kb_queue[kb_index++] = '\0';
    if(kb_index == KB_RING_SIZE)
        kb_index = 0;

    return c;
}

void keyboard_read(char *str, uint16_t length) {
    _kb_internal_ptr = 0;
    kb_index = 0;
    for(uint8_t i = 0; i < KB_RING_SIZE; i++)
        kb_queue[i] = '\0';
    
    for(uint16_t i = 0; i < length - 1; i++) {
        str[i] = _keyboard_readchar();
        if(str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }

    str[length - 1] = '\0';
}