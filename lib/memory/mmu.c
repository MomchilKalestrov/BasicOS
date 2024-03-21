#define MMU_SIZE 512

struct mmu_cell {
    uint8_t *address;
    bool is_used;
    size_t size;
} __attribute__((packed));

struct mmu_cell mmu_table[MMU_SIZE];
uint8_t mmu_data[MMU_SIZE];

size_t mmu_enough_space(int16_t index, size_t size) {
    size_t i;
    for(i = 0; i < size; ++i)
        if(mmu_table[i + index].is_used) return i;
    return i;
}

uint8_t *mmu_allocate(size_t size) {
    for(size_t i = 0; i < MMU_SIZE; ++i)
        if(!mmu_table[i].is_used)
            if(mmu_enough_space(i, size) >= size) {
                for(size_t j = 0; j < size; ++j) {
                    mmu_table[i + j].is_used = true;
                }
                mmu_table[i].size = size;
                return (uint8_t *)mmu_table[i].address;
            }
    terminal_fatal("MMU out of memory");
    return (uint8_t *)0;
}

void mmu_free(void *address) {
    uint16_t index = address - (void *)&mmu_data;
    size_t size = mmu_table[index].size;

    for(size_t i = 0; i < size; ++i) {
        *mmu_table[i + index].address = 0;
        mmu_table[i + index].is_used = false;
        mmu_table[i + index].size = 0;
    }
}

void mmu_init() {
    mmu_table[0].address = (uint8_t *)&mmu_data[0];
    for(int16_t i = 1; i < MMU_SIZE; ++i)
        mmu_table[i].address = mmu_table[i - 1].address + 1;
}
