void _syscall_read_file(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    uint16_t buffer_length = (uint16_t)(eax & 0x00FFFFFF);
    uint8_t *buffer = (uint8_t *)ebx;
    file_t *file = (file_t *)ecx;

    drive_readfile(*file, buffer, buffer_length);
}

void _syscall_open_file(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    uint16_t buffer_length = (uint16_t)(eax & 0x0000FFFF);
    char *name = (char *)ebx;
    file_t *file = (file_t *)ecx;

    *file = drive_getfile(name);
}

void _syscall_get_files(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    uint16_t buffer_length = (uint16_t)(eax & 0x0000FFFF);
    file_t *buffer = (file_t *)ebx;

    for(uint8_t i = 0; i < buffer_length / sizeof(file_t); i++)
        buffer[i] = dirs[i];
}

_calls read_calls[] = {
    _syscall_read_file,
    _syscall_open_file,
    _syscall_get_files
};