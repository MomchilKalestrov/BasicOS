#include "./mouse.h"

uint16_t mouse_x = 64;
uint16_t mouse_y = 64;

uint8_t mouse_left   = 0;
uint8_t mouse_center = 0;
uint8_t mouse_right  = 0;

uint32_t cursor_back[CURSOR_SIZE][CURSOR_SIZE];
const uint8_t cursor[CURSOR_SIZE][CURSOR_SIZE] = {
    { 1,1,0,0,0,0,0,0,0,0,0,0, },
    { 1,2,1,1,0,0,0,0,0,0,0,0, },
    { 0,1,2,2,1,1,0,0,0,0,0,0, },
    { 0,1,2,2,2,2,1,1,0,0,0,0, },
    { 0,0,1,2,2,2,2,2,1,1,0,0, },
    { 0,0,1,2,2,2,2,2,2,2,1,1, },
    { 0,0,0,1,2,2,2,2,2,2,1,0, },
    { 0,0,0,1,2,2,2,2,2,1,0,0, },
    { 0,0,0,0,1,2,2,2,2,1,0,0, },
    { 0,0,0,0,1,2,2,1,1,2,1,0, },
    { 0,0,0,0,0,1,1,0,0,1,2,1, },
    { 0,0,0,0,0,1,0,0,0,0,1,1, },
};

void mouse_update(int32_t new_x, int32_t new_y) {
    for(uint8_t y = 0; y < CURSOR_SIZE; y++)
        for(uint8_t x = 0; x < CURSOR_SIZE; x++)
            graphics_pixel(mouse_x + x, mouse_y + y, cursor_back[y][x]);

    for(uint8_t y = 0; y < CURSOR_SIZE; y++)
        for(uint8_t x = 0; x < CURSOR_SIZE; x++)
            cursor_back[y][x] = graphics_getpixel(new_x + x, new_y + y);

    for(uint8_t y = 0; y < CURSOR_SIZE; y++)
        for(uint8_t x = 0; x < CURSOR_SIZE; x++)
            if(cursor[y][x])
                graphics_pixel(new_x + x, new_y + y, mouse_colors[cursor[y][x]]);

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