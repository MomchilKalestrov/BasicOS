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