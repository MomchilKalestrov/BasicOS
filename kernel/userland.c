void close(element_t *e) {
    element_remove(element_counter - 1);
    element_remove(element_counter - 1);
    graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
    elements = _elements_arr;
    element_render();
}

void file_clicked(element_t *e) {
    char *extention = e->text + 8;
    if(string_compare(extention, "ELF")) {
        file_t file = drive_getfile(e->text);
        size_t len = 512;
        while(len < file.file_size)
            len += 512;
        uint8_t buf[len];
        drive_readfile(file, buf, len);
        binary_execute(buf, len);

        foreground = 0xf5ded3;
        background = 0x75300D;
        elements = _elements_arr;
        graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
        element_render();
    }
    else if(string_compare(extention, "TGA")) {
        file_t *file = (file_t *)mmu_allocate(sizeof(file_t), true);
        *file = drive_getfile(e->text);
        
        element_t img_e = {
            .x = 0,
            .y = 0,
            .width = 256,
            .height = 256,
            .foreground = 0,
            .background = 0,
            .text = "",
            .type = IMAGE,
            .visible = true
        };
        image_t *img_d = (image_t *)img_e.extras;
        img_d->image_location = file;
        element_load(img_e);

        elements = &elements[element_counter - 1];

        element_t btn_e = {
            .x = 0,
            .y = framebuffer_height - 32,
            .width = 81,
            .height = 32,
            .foreground = 0x75300D,
            .background = 0xFFFFFF,
            .visible = true,
            .text = "Close",
        };
        button_t *btn_d = (button_t *)btn_e.extras;
        btn_d->on_click = close;
        element_load(btn_e);
        
        graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
        element_render();
    }
    else if(string_compare(extention, "TXT")) {
        file_t file = drive_getfile(e->text);
        graphics_text(128, 0, file.file_name);
    }
}

void enter_userland(void) {
    for(size_t i = 0; i < dir_counter; i++) {
        element_load((element_t) {
            .x = 1,
            .y = 1 + i * 33,
            .width = 117,
            .height = 32,
            .foreground = 0x75300D,
            .background = 0xFFFFFF,
            .text = dirs[i].file_name,
            .type = BUTTON,
            .visible = true
        });
        ((button_t *)elements[i].extras)->on_click = file_clicked;
    }
    element_render();
    foreground = 0xf5ded3;
    background = 0x75300D;
}