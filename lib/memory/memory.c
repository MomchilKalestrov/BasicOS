#define MEMORY_POOL_SIZE 1024
#define BH_SIZE 8

typedef struct {
    size_t size;
    int is_allocated;
} BlockHeader;

typedef struct {
    uint8_t memory_pool[MEMORY_POOL_SIZE];
} MemoryManager;

MemoryManager *manager;

void memory_init(void) {
    BlockHeader *header = (BlockHeader *)manager->memory_pool;
    header->size = MEMORY_POOL_SIZE - BH_SIZE;
    header->is_allocated = 0;
}

void *memory_allocate(size_t size) {
    BlockHeader *current = (BlockHeader *)manager->memory_pool;

    while (current->size < size || current->is_allocated) {
        current = (BlockHeader *)((uint8_t *)current + BH_SIZE + current->size);

        if ((uint8_t *)current >= manager->memory_pool + MEMORY_POOL_SIZE)
            return NULL;
    }

    current->is_allocated = 1;

    if (current->size > size + BH_SIZE) {
        BlockHeader *new_free_block = (BlockHeader *)((unsigned char *)current + BH_SIZE + size);
        new_free_block->size = current->size - size - BH_SIZE;
        new_free_block->is_allocated = 0;
        current->size = size;
    }

    return (void *)(current + 1);
}

void memory_free(void *ptr) {
    if (ptr != NULL) {
        BlockHeader *header = ((BlockHeader *)ptr) - 1;
        header->is_allocated = 0;
    }
}

/*
int memory_new() {
    MemoryManager myMemoryManager;
    initializeMemoryManager(&myMemoryManager);

    // Allocate memory from the pool
    void *memory1 = custom_malloc(&myMemoryManager, 64);
    void *memory2 = custom_malloc(&myMemoryManager, 128);

    // Print the addresses of allocated memory
    printf("Allocated memory addresses: %p, %p\n", memory1, memory2);

    // Free the allocated memory
    custom_free(&myMemoryManager, memory1);
    custom_free(&myMemoryManager, memory2);

    return 0;
}
*/