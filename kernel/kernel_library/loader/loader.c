void binary_execute(uint8_t *buffer, size_t length) {
    if(length < sizeof(elf_header_t) || length > 0x400000)
        return;
    
    // write to start
    for(size_t i = 0; i < length; i++)
        *(uint8_t *)i = buffer[i];

    // enter
    elf_header_t *header = (elf_header_t *)buffer;
    entry_point_t entry_point = (entry_point_t)header->e_entry;
    entry_point();
    asm("sti");
}