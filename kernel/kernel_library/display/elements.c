void element_load(element_t element) {
    if(element_counter > MAX_ELEMENTS) {
        graphics_text(0, 0, "Element limit reached");
        return;
    }

    elements[element_counter++] = element;
}

void element_remove(uint8_t index) {
    if(index >= element_counter) {
        element_counter--;
        return;
    }

    for(uint8_t i = index; i < element_counter - 1; i++)
        elements[i] = elements[i + 1];
    
    element_counter--;
}

void element_clicked() {
    for(uint8_t i = 0; i < element_counter; i++) {
        element_t e = elements[i];
        if(mouse_x < e.x || mouse_x > e.x + e.width) continue;
        if(mouse_y < e.y || mouse_y > e.y + e.height) continue;
        
        if(!e.visible) continue;

        switch (e.type)
        {
            case BUTTON:
                button_t *b = (button_t *)e.extras;
                b->on_click(&elements[i]);
                return;
            case FIELD: 
                element_selected = i;
                graphics_rectangle(e.x, e.y, e.x + 3, e.y + 3, FILLED);
                return;
        }
    }
}

void element_edit(char symbol) {
    if(element_selected == -1) return;

    element_t e = elements[element_selected];
    if(e.type != FIELD) return;

    uint8_t *index = &(((field_t *)e.extras)->selected_index);

    if(symbol == '\b') {
        if(*index != 0)
            e.text[--*index] = '\0';
        
        element_render();
        return;
    }
    e.text[(*index)++] = symbol;
    element_render();
}

void _render_button(element_t e) {
    foreground = e.foreground;
    background = e.background;
    graphics_rectangle(e.x, e.y, e.width, e.height, FILLED);
    foreground = e.background;
    background = e.foreground;

    size_t len = string_length(e.text);
    if(len < e.width / 8)
        graphics_text(e.x + e.width / 2 - len * 4, e.y + e.height / 2 - 8, e.text);
    else {
        char *ptr = e.text + (len - e.width / 8);
        size_t short_len = string_length(ptr);
        graphics_text(e.x + e.width / 2 - short_len * 4, e.y + e.height / 2 - 8, ptr);
    }
}

void _render_field(element_t e, bool selected) {
    foreground = e.foreground;
    graphics_rectangle(e.x, e.y, e.width, e.height, HOLLOW);
    foreground = e.background;
    graphics_rectangle(e.x + 1, e.y + 1, e.width - 2, e.height - 2, FILLED);
    foreground = e.foreground;
    background = e.background;
    
    size_t len = string_length(e.text);
    if(len < e.width / 8)
        graphics_text(e.x + e.width / 2 - len * 4, e.y + e.height / 2 - 8, e.text);
    else {
        char *ptr = e.text + (len - e.width / 8);
        size_t short_len = string_length(ptr);
        graphics_text(e.x + e.width / 2 - short_len * 4, e.y + e.height / 2 - 8, ptr);
    }

    if(selected)
        graphics_rectangle(e.x, e.y, e.x + 3, e.y + 3, FILLED);
}

void _render_image(element_t e) {
    // Why the fuck did I place comments only HERE
    // get FAT32 data
    file_t file = *(((image_t *)e.extras)->image_location);
    size_t len = 512;
    while(len < file.file_size) len += 512;
	uint8_t *buffer = (uint8_t *)mmu_allocate(len, true);
    // read file
	drive_readfile(file, buffer, len);
    // get TGA header
	tga_header_t *header = (tga_header_t *)buffer;
    // render
	uint32_t *data = (uint32_t *)(buffer + sizeof(tga_header_t) + header->id_length);
	for(size_t y = 0; y < header->height && y < e.height; y++)
		for(size_t x = 0; x < header->width && x < e.width; x++)
			graphics_pixel(x, e.y + header->height - y - 1, data[y * header->width + x]);
}

void element_render() {
    uint32_t fg = foreground;
    uint32_t bg = background;

    for(uint16_t i = 0; i < element_counter; i++) {
        if(!elements[i].visible) continue;
        switch (elements[i].type) {
            case BUTTON: _render_button(elements[i]); break;
            case FIELD:  _render_field(elements[i], i == element_selected); break;
            case IMAGE:  _render_image(elements[i]); break;
        }
    }

    foreground = fg;
    background = bg;
}