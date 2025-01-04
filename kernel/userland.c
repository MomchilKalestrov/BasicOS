void close(element_t *e) {
    element_remove(element_counter - 1);
    element_remove(element_counter - 1);
    graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
    elements = _elements_arr;
    element_render();
}

void file_clicked(void *e) {
    element_t *element = (element_t *)e;
    char *extention = element->text + 8;
    if(string_compare(extention, "ELF")) {
        file_t file = drive_getfile(element->text);
        size_t len = 512;
        while(len < file.file_size)
            len += 512;

        uint8_t *buf = (uint8_t *)mmu_allocate(len, true);
        drive_readfile(file, buf, len);
        binary_execute(buf, len);

        elements = _elements_arr;
        element_render();
        mmu_free(buf);
    }
    else if(string_compare(extention, "TGA")) {
        file_t *file = (file_t *)mmu_allocate(sizeof(file_t), true);
        *file = drive_getfile(element->text);
        
        element_t img = {
            .x = 0,
            .y = 0,
            .width = 256,
            .height = 256,
            .foreground = 0,
            .background = 0,
            .text = "",
            .type = IMAGE,
            .visible = true,
            .image = { .image_location = file }
        };
        element_load(img);

        elements = &elements[element_counter - 1];

        element_t btn = {
            .x = 0,
            .y = framebuffer_height - 32,
            .width = 81,
            .height = 32,
            .foreground = 0x75300D,
            .background = 0xFFFFFF,
            .visible = true,
            .text = "Close",
            .type = BUTTON,
            .button = { .on_click = close }
        };
        element_load(btn);
    
        graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
        element_render();
    }
    else if(string_compare(extention, "TXT")) {
        file_t file = drive_getfile(element->text);
        graphics_text(128, 0, file.file_name);
    }
}

void enter_userland(void) {
    for(size_t i = 0; i < dir_counter; i++) {
        element_load((element_t) {
            .x = 1,
            .y = 1 + i * 33,
            .width = 106,
            .height = 32,
            .foreground = 0x75300D,
            .background = 0xFFFFFF,
            .text = dirs[i].file_name,
            .type = BUTTON,
            .visible = true,
            .button = { .on_click = file_clicked }
        });
    }
	graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
    element_render();

    for(;;) {
        asm("hlt");
        event_t e = event_pop();
        if(e.type == EVENT_MOUSE_CLICK)
            element_clicked();
    }

    foreground = 0xf5ded3;
    background = 0x75300D;
}