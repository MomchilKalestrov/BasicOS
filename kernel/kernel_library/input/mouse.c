void mouse_update(int32_t new_x, int32_t new_y) {
    for(uint8_t y = 0; y < CURSOR_SIZE; y++)
        for(uint8_t x = 0; x < CURSOR_SIZE; x++)
            graphics_pixel(mouse_x + x, mouse_y + y, cursor_back[y][x]);

    for(uint8_t y = 0; y < CURSOR_SIZE; y++)
        for(uint8_t x = 0; x < CURSOR_SIZE; x++)
            cursor_back[y][x] = graphics_getpixel(new_x + x, new_y + y);

    for(uint8_t y = 0; y < CURSOR_SIZE; y++)
        for(uint8_t x = 0; x < CURSOR_SIZE; x++)
            switch (cursor[y][x])
            {
                case 1: graphics_pixel(new_x + x, new_y + y, 0x000000); break;
                case 2: graphics_pixel(new_x + x, new_y + y, 0xffffff); break;
            }

    mouse_x = new_x;
    mouse_y = new_y;
}

void mouse_init(void) {
    mouse_update(64, 64);

    // Enable the mouse
    outb(0x64, 0xA8);
    // Get the current config and enable the mouse IRQ
    outb(0x64, 0x20);
    uint8_t status = inb(0x60) | 0b00000010;
    outb(0x64, 0x60);
    outb(0x60, status);

    // Initialize
    outb(0x64, 0xD4);
    outb(0x60, 0xFF);
    inb(0x60);

    outb(0x64, 0xD4);
    outb(0x60, 0xF6);
    inb(0x60);

    outb(0x64, 0xD4);
    outb(0x60, 0xF4);
    inb(0x60);
}