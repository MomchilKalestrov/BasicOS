void binary_execute(uint8_t *buffer, size_t length) {
    if(length < sizeof(elf_header_t) || length > 0x400000)
        return;

    elements = &_elements_arr[element_counter - 1];
    foreground = 0;
    background = 0;
    graphics_rectangle(0, 0, framebuffer_width, framebuffer_height, 0);
    foreground = 0xffffff;
    
    for(size_t i = 0; i < length; i++)
        *(uint8_t *)i = buffer[i];

    elf_header_t *header = (elf_header_t *)buffer;
    entry_point_t entry_point = (entry_point_t)header->e_entry;
    entry_point();
}