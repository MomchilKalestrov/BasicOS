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
            uint32_t id_set = eax & 0x00ffffff;
            *(uint32_t *)(variables[id_set]) = ebx;
            return;
        case COMMAND_GET:
            uint32_t id_get = eax & 0x00ffffff;
            return_value = *(uint32_t *)(variables[id_get]);
            has_return = true;
            return;
    }
}