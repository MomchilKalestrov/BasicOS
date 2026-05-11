void _get_total_memory() {
    total_memory = 0;

    if (mb_info->flags & (1 << 6)) {
        multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)mb_info->mmap_addr;
        while ((uint32_t)mmap < mb_info->mmap_addr + mb_info->mmap_length) {
            if (mmap->type == 1)
                total_memory += mmap->len;
            mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
        }
    }
}

void _paging_init(void) {
    _get_total_memory();

    size_t i, j;
    for(i = 0; i < 1024; i++)
        page_directory[i] = 0x00000002;
    
    for(i = 0; i < 1024; i++)
        page_tables[0].entries[i] = (i * 0x1000) | 7;

    for(j = 1; j < TABLES - 3; j++)
        for(i = 0; i < 1024; i++)
            page_tables[j].entries[i] = ((i + (j * 1024)) * 0x1000) | 3;
            
    for(i = 0; i < 1024; i++)
        page_tables[6].entries[i] = (mb_info->framebuffer_addr + (i * 0x1000)) | 3;
    for(i = 0; i < 1024; i++)
        page_tables[7].entries[i] = ((uint32_t)k_heap + (i * 0x1000)) | 0;
    for(i = 0; i < 1024; i++)
        page_tables[8].entries[i] = ((uint32_t)heap + (i * 0x1000)) | 7;

    for(j = 0; j < TABLES; j++)
        page_directory[j] = ((uint32_t)&page_tables[j].entries) | 3;

    asm (
        "mov %0, %%cr3\n"
        "mov %%cr0, %%eax\n"
        "or $0x80000001, %%eax\n"
        "mov %%eax, %%cr0"
        :
        : "r" (page_directory)
        : "eax"
    );
}

void _swap_pages(uint32_t first, uint32_t second) {
    uint32_t temp = page_directory[first];
    page_directory[first] = page_directory[second];
    page_directory[second] = temp;

    asm (
        "mov %%cr3, %%eax\n"
        "mov %%eax, %%cr3"
        : : : "eax"
    );
}