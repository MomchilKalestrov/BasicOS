#ifndef _DISPLAY_
#define _DISPLAY_

#include <stdint.h>

#include "../multiboot.h"

#define HOLLOW 1
#define FILLED 0

extern multiboot_info_t *mb_info;

extern uint32_t *framebuffer;

extern uint32_t framebuffer_width;
extern uint32_t framebuffer_height;

extern uint32_t foreground;
extern uint32_t background;

void graphics_init(void);
void graphics_pixel(uint16_t, uint16_t, uint32_t);
uint32_t graphics_getpixel(uint16_t, uint16_t);
void graphics_glyph(uint16_t, uint16_t, char);
void graphics_character(uint16_t *, uint16_t *, char);
void graphics_text(uint16_t, uint16_t , char *);
void graphics_rectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t);
void graphics_circle(uint16_t, uint16_t, uint16_t, uint8_t);
void graphics_line(uint16_t, uint16_t, uint16_t, uint16_t);

#endif