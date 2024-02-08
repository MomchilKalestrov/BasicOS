void filesystem_poll() {
    while ((inb(0x1F7) & 0x80) != 0);
}

void filesystem_readsector(uint8_t sector, uint8_t* buffer) {
    filesystem_poll();

    outb(0x1F6, 0xE0 | (0 << 4));
    outb(0x1F2, 1);    
    outb(0x1F3 , sector);
    outb(0x1F4, 0);    
    outb(0x1F5, (0 >> 8) & 0xFF);
    outb(0x1F6, 0xE0 | (0 << 4) | ((0 >> 8) & 0x0F));
    outb(0x1F7, 0x20);
    
    filesystem_poll();

    for (int i = 0; i < 256; ++i) {
        uint16_t word = inw(0x1F0);
        buffer[i * 2] = (uint8_t)word;
        buffer[i * 2 + 1] = (uint8_t)(word >> 8);
    }
}
