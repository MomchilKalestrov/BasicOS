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
        element_t element = elements[i];
        if(mouse_x < element.x || mouse_x > element.x + element.width) continue;
        if(mouse_y < element.y || mouse_y > element.y + element.height) continue;
        
        if(!element.visible) continue;

        switch (element.type)
        {
            case BUTTON:
                if (element.button.on_click)
                    element.button.on_click((void *)&elements[i]);
                return;
            case FIELD: 
                element_selected = i;
                graphics_rectangle(element.x, element.y, element.x + 3, element.y + 3, FILLED);
                return;
        }
    }
}

void element_edit(char symbol) {
    if(element_selected == -1) return;

    element_t element = elements[element_selected];
    if(element.type != FIELD) return;

    uint8_t *index = &element.field.selected_index;

    if(symbol == '\b') {
        if(*index != 0)
            element.text[--*index] = '\0';
        
        element_render();
        return;
    }
    element.text[(*index)++] = symbol;
    element_render();
}

void _render_button(element_t element) {
    foreground = element.foreground;
    background = element.background;
    graphics_rectangle(element.x, element.y, element.width, element.height, FILLED);
    foreground = element.background;
    background = element.foreground;

    size_t len = string_length(element.text);
    if(len < element.width / 8)
        graphics_text(element.x + element.width / 2 - len * 4, element.y + element.height / 2 - 8, element.text);
    else {
        char *ptr = element.text + (len - element.width / 8);
        size_t short_len = string_length(ptr);
        graphics_text(element.x + element.width / 2 - short_len * 4, element.y + element.height / 2 - 8, ptr);
    }
}

void _render_field(element_t element, bool selected) {
    foreground = element.foreground;
    graphics_rectangle(element.x, element.y, element.width, element.height, HOLLOW);
    foreground = element.background;
    graphics_rectangle(element.x + 1, element.y + 1, element.width - 2, element.height - 2, FILLED);
    foreground = element.foreground;
    background = element.background;
    
    size_t len = string_length(element.text);
    if(len < element.width / 8)
        graphics_text(element.x + element.width / 2 - len * 4, element.y + element.height / 2 - 8, element.text);
    else {
        char *ptr = element.text + (len - element.width / 8);
        size_t short_len = string_length(ptr);
        graphics_text(element.x + element.width / 2 - short_len * 4, element.y + element.height / 2 - 8, ptr);
    }

    if(selected)
        graphics_rectangle(element.x, element.y, element.x + 3, element.y + 3, FILLED);
}

void _render_image(element_t element) {
    // Why the fuck did I place comments only HERE
    // get FAT32 data
    file_t file = *(element.image.image_location);
    size_t len = 512;
    while(len < file.file_size) len += 512;
	uint8_t *buffer = (uint8_t *)mmu_allocate(len, true);
    // read file
	drive_readfile(file, buffer, len);
    // get TGA header
	tga_header_t *header = (tga_header_t *)buffer;
    // render
	uint32_t *data = (uint32_t *)(buffer + sizeof(tga_header_t) + header->id_length);
	for(size_t y = 0; y < header->height && y < element.height; y++)
		for(size_t x = 0; x < header->width && x < element.width; x++)
			graphics_pixel(x, element.y + header->height - y - 1, data[y * header->width + x]);
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