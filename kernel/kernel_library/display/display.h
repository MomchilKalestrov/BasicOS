#ifndef _DISPLAY_
    #define _DISPLAY_

    #define HOLLOW 1
    #define FILLED 0

    uint32_t *framebuffer = (uint32_t *)0x1800000;

    uint32_t framebuffer_width;
    uint32_t framebuffer_height;

    uint32_t foreground;
    uint32_t background;
    
    void graphics_init(void);
    void graphics_pixel(uint16_t x, uint16_t y, uint32_t pixel);
    uint32_t graphics_getpixel(uint16_t x, uint16_t y);
    void graphics_glyph(uint16_t x, uint16_t y, char glyph);
    void graphics_character(uint16_t *x, uint16_t *y, char character);
    void graphics_text(uint16_t x, uint16_t y, char *text);

    #include "./display.c"
#endif