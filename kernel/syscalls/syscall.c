#include "./syscall.h"

uint32_t return_value;
bool has_return;

uint32_t *variables[] = {
    (uint32_t *)&foreground,
    (uint32_t *)&background
};

void _handle_syscall(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    uint8_t syscall_type = (eax & 0x00FF0000) >> 16;
    switch(eax & 0xFF000000) {
        case COMMAND_READ:
            read_calls[syscall_type](eax, ebx, ecx);
            return;
        case COMMAND_WRITE:
            write_calls[syscall_type](eax, ebx, ecx);
            return;
        case COMMAND_SET: {
            uint32_t id = eax & 0x00ffffff;
            *(variables[id]) = ebx;
            return;
        } case COMMAND_GET: {
            // redeclaring `id`, so we need the braces
            uint32_t id = eax & 0x00ffffff;
            return_value = *(variables[id]);
            has_return = true;
            return;
        }
    }
}