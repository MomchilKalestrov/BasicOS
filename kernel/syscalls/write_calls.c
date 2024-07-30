void _syscall_write_file(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    uint16_t buffer_length = (uint16_t)(eax & 0x0000FFFF);
    uint8_t *buffer_ptr = (uint8_t *)ebx;
    file_t *file = (file_t *)ecx;

    graphics_text(0, 0, "NOT IMPLEMENTED");
}

void _syscall_write_figure(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    switch (eax & 0x000000FF)
    {
        case FIG_TYPE_LINE:
            graphics_line(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                ecx >> 16, (uint16_t)ecx & 0x0000FFFF
            );
            break;
        case FIG_TYPE_RECT:
            graphics_rectangle(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                ecx >> 16, (uint16_t)ecx & 0x0000FFFF,
                (eax & 0x0000FF00) >> 8
            );
            break;
        case FIG_TYPE_CIRC:
            graphics_circle(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                ecx >> 16,
                (eax & 0x0000FF00) >> 8
            );
            break;
        case FIG_TYPE_TEXT:
            graphics_text(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                (char *)ecx
            );
            break;
    }
}

void _syscall_write_element(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    element_load(*((element_t *)ebx));
    element_render();
}

_calls write_calls[] = {
    _syscall_write_file,
    _syscall_write_figure,
    _syscall_write_element
};