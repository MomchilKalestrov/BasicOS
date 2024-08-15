void irq_timer(void) {
	pic_sendEOI(0);
}

void irq_readkey(void) {
	uint8_t scancode;
	uint8_t character;

	uint8_t interface_check = inb(0x64) & 0x20;
	if(interface_check)
		goto end;

	scancode = inb(0x60);

	switch (scancode) {
		case 0x2a:
		case 0x36:
			mod_keys |= MOD_SHIFT;
			goto end;
		case 0xaa:
		case 0xb6:
			mod_keys &= ~MOD_SHIFT;
			goto end;

		case 0x1d:
			mod_keys |= MOD_CTRL;
			goto end;
		case 0x9d:
			mod_keys &= ~MOD_CTRL;
			goto end;

		case 0x38:
			mod_keys |= MOD_ALT;
			goto end;
		case 0xb8:
			mod_keys &= ~MOD_ALT;
			goto end;

		// case 0x48: return terminal_putchar(0x18); // up
		// case 0x4b: return terminal_putchar(0x1b); // left
		// case 0x50: return terminal_putchar(0x19); // down
		// case 0x4D: return terminal_putchar(0x1a); // right
	}

	if (scancode & 0x80 || scancode == 0xe0)
		goto end;

	if(mod_keys & MOD_SHIFT)
		character = keyboard_layout_shift[scancode];
	else
		character = keyboard_layout[scancode];

	kb_queue[_kb_internal_ptr++] = character;
	if(_kb_internal_ptr == KB_RING_SIZE)
		_kb_internal_ptr = 0;

	if(kb_event)
		kb_event(mod_keys, character);

	end:
	pic_sendEOI(1);
}

void irq_readmouse(void) {
	static uint8_t buttons = 0;
    static uint8_t mouse_cycle = 0;
    static uint8_t mouse_byte[3];

    uint8_t interface_check = inb(0x64) & 0x20;
    if(!interface_check)
		goto end;

    mouse_byte[mouse_cycle++] = inb(0x60);

	// Align the actual packets
	if(!(mouse_byte[0] & 0b00001000)) {
		mouse_cycle = 0;
		goto end;
	}

    if(mouse_cycle == 3) {
        mouse_cycle = 0;

		uint8_t state = mouse_byte[0];
		uint8_t x     = mouse_byte[1];
		uint8_t y     = mouse_byte[2];

		int32_t new_x = mouse_x + (x - ((state << 4) & 0x100));
		int32_t new_y = mouse_y - (y - ((state << 3) & 0x100));


		if(new_x < 1) new_x = 1;
		if(new_y < 1) new_y = 1;
		if(new_x > (int32_t)(mb_info->framebuffer_width - 1)) new_x = mb_info->framebuffer_width - 1;
		if(new_y > (int32_t)(mb_info->framebuffer_height - 1)) new_y = mb_info->framebuffer_height - 1;
		
		mouse_update(new_x, new_y);

		event_t event = {
			.mouse_event = {
				.x = new_x,
				.y = new_y
			}
		};

		if(state & 0b00000111)	event.type = buttons ? MOUSE_DRAG : MOUSE_CLICK;
		else if (buttons)		event.type = MOUSE_RELEASE;
		else					event.type = MOUSE_MOVE;

		event_push(event);

		buttons = state & 0b00000111;
    }

	end: pic_sendEOI(12);
}

void irq_coprocessor() {
	pic_sendEOI(13);
}

void irq_primaryATA() {
	pic_sendEOI(14);
}

void irq_secondaryATA() {
	pic_sendEOI(15);
}