void _handle_syscall(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    uint8_t syscall_type = (eax & 0x00FF0000) >> 16;
    switch(eax & 0xFF000000) {
        case COMMAND_READ:
            read_calls[syscall_type](eax, ebx, ecx);
            return;
        case COMMAND_WRITE:
            write_calls[syscall_type](eax, ebx, ecx);
            return;
        case COMMAND_SET:
            *((uint32_t *)setters[eax & 0x00ffffff]) = ebx;
            return;
        case COMMAND_GET:
            return_value = *((uint32_t *)getters[eax & 0x00ffffff]);
            has_return = true;
            return;
    }
}