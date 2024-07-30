void graphics_init(void) {
    foreground = 0x00ffffff;
    background = 0x00000000;

    framebuffer_width = mb_info->framebuffer_width;
    framebuffer_height = mb_info->framebuffer_height;

    framebuffer = (uint32_t *)0x1800000;
    for (uint16_t y = 0; y < framebuffer_height; y++)
        for (uint16_t x = 0; x < framebuffer_width; x++)
            framebuffer[y * framebuffer_width + x] = background;
}

void graphics_pixel(uint16_t x, uint16_t y, uint32_t pixel) {
    if(x > framebuffer_width - 1 || y > framebuffer_height - 1) return;
    framebuffer[y * framebuffer_width + x] = pixel;
}

uint32_t graphics_getpixel(uint16_t x, uint16_t y) {
    return framebuffer[y * framebuffer_width + x];
}

void graphics_glyph(uint16_t x, uint16_t y, char glyph) {
    uint8_t *glyph_binary = &font[4 + (uint8_t)glyph * 16];
    for(uint8_t i = 0; i < 16; i++)
        for(uint8_t j = 0; j < 8; j++)
            if(glyph_binary[i] & (1 << j)) graphics_pixel(x + (8 - j), y + i, foreground);
                else                       graphics_pixel(x + (8 - j), y + i, background);
}

void graphics_character(uint16_t *x, uint16_t *y, char character) {
    switch(character) {
        case '\b':
            *x -= 9;
            graphics_glyph(*x, *y, ' ');
            *x -= 9;
            break;
        case '\t':
            *x += 9 * 4;
            break;
        case '\n':
            *x = -9;
            *y += 16;
            break;
        default:
            graphics_glyph(*x, *y, character);
            break;
    }
}

void graphics_text(uint16_t x, uint16_t y, char *text) {
    char *address = text;
    uint16_t glyph_x = x;
    uint16_t glyph_y = y;
    
    while(*address != '\0') {
        graphics_character(&glyph_x, &glyph_y, *address);
        glyph_x += 9;
        address++;
    }
}

void graphics_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t type) {
    for(uint16_t i = 0; i < height; i++)
        for(uint16_t j = 0; j < width; j++)
            if(type == FILLED)
                graphics_pixel(x + j, y + i, foreground);
            else if(i == 0 || i == height - 1 || j == 0 || j == width - 1)
                graphics_pixel(x + j, y + i, foreground);
}

void graphics_circle(uint16_t center_x, uint16_t center_y, uint16_t radius, uint8_t type) {
    int16_t x = 0;
    int16_t y = radius;
    int16_t p = 3 - (2 * radius);

    for(x = 0; x <= y; x++) {
        graphics_pixel(center_x + x, center_y - y, 0x00ffffff);

        if(p < 0) p=(p+(4*x)+1);
        else      p += (4 * (x - --y) + 1);

        graphics_pixel(center_x + x, center_y - y, 0x00ffffff);
        graphics_pixel(center_x - x, center_y - y, 0x00ffffff);
        graphics_pixel(center_x + x, center_y + y, 0x00ffffff);
        graphics_pixel(center_x - x, center_y + y, 0x00ffffff);
        graphics_pixel(center_x + y, center_y - x, 0x00ffffff);
        graphics_pixel(center_x - y, center_y - x, 0x00ffffff);
        graphics_pixel(center_x + y, center_y + x, 0x00ffffff);
        graphics_pixel(center_x - y, center_y + x, 0x00ffffff);

        if(type == FILLED) {
            for(uint16_t i = center_x - x; i < center_x + x; i++){
                graphics_pixel(i, center_y + y, foreground);
                graphics_pixel(i, center_y - y, foreground);
            }
            for(uint16_t i = center_x - y; i <= center_x + y; i++) {
                graphics_pixel(i, center_y + x, foreground);
                graphics_pixel(i, center_y - x, foreground);
            }
        }
    }
}

void graphics_line(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y) {
    int16_t delta_x = end_x - start_x;
    int16_t delta_y = end_y - start_y;

    uint16_t abs_delta_x = (delta_x ^ (delta_x >> 31)) - (delta_x >> 31);
    uint16_t abs_delta_y = (delta_y ^ (delta_y >> 31)) - (delta_y >> 31);

    uint8_t sign_x = delta_x > 0 ? 1 : -1;
    uint8_t sign_y = delta_y > 0 ? 1 : -1;

    int16_t x = start_x;
    int16_t y = start_y;

    if (abs_delta_x > abs_delta_y) {
        int16_t p = 2 * abs_delta_y - abs_delta_x;
        for (int16_t i = 0; i <= abs_delta_x; i++) {
            graphics_pixel(x, y, foreground);
            x += sign_x;
            if (p >= 0) {
                y += sign_y;
                p -= 2 * abs_delta_x;
            }
            p += 2 * abs_delta_y;
        }
    } else {
        int16_t p = 2 * abs_delta_x - abs_delta_y;
        for (int16_t i = 0; i <= abs_delta_y; i++) {
            graphics_pixel(x, y, foreground);
            y += sign_y;
            if (p >= 0) {
                x += sign_x;
                p -= 2 * abs_delta_y;
            }
            p += 2 * abs_delta_x;
        }
    }
}