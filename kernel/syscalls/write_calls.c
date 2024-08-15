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
        case FIG_TYPE_RECTANGLE:
            graphics_rectangle(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                ecx >> 16, (uint16_t)ecx & 0x0000FFFF,
                (eax & 0x0000FF00) >> 8
            );
            break;
        case FIG_TYPE_CIRCLE:
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
        case FIG_TYPE_PIXEL:
            graphics_pixel(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                ecx
            );
        case FIG_TYPE_SYMBOL:
            graphics_symbol(
                ebx >> 16, (uint16_t)ebx & 0x0000FFFF,
                ecx
            );
            break;
    }
}

_calls write_calls[] = {
    _syscall_write_file,
    _syscall_write_figure
};