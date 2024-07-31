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
    filename_t *buffer = (filename_t *)ebx;

    for(size_t i = 0; i < buffer_length / sizeof(filename_t); i++)
        for(size_t j = 0; j < 11; j++)
            buffer[i][j] = dirs[i].file_name[j];
}

_calls read_calls[] = {
    _syscall_read_file,
    _syscall_open_file,
    _syscall_get_files
};