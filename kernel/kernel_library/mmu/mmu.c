void mmu_init(void) {
    mmu_head = (mmu_node_t *)heap;
    mmu_head->size = MMU_HEAP_SIZE - sizeof(mmu_node_t);
    mmu_head->is_free = 1;
    mmu_head->next = NULL;
    // I'm so brainrotted I forgot to initialize the kernel MMU
    // and when you allocated from it you allways got a null pointer
    // But now it works :)
    mmu_k_head = (mmu_node_t *)k_heap;
    mmu_k_head->size = MMU_HEAP_SIZE - sizeof(mmu_node_t);
    mmu_k_head->is_free = 1;
    mmu_k_head->next = NULL;
}

mmu_node_t *_get_first_free_block(size_t size, bool kernel) {
    mmu_node_t *current = kernel ? mmu_k_head : mmu_head;
    while(current) {
        if(current->is_free && current->size >= size)
            return current;
        current = current->next;
    }
    return NULL;
}

void *mmu_allocate(size_t size, bool kernel) {
    if(!size) return NULL;

    mmu_node_t *block = _get_first_free_block(size, kernel);

    if(!block) return NULL;

    block->is_free = 0;
    block->size = size;

    // If the block cannot be split into two blocks, add the rest of the bytes and return the block
    if(block->next - block - size - sizeof(mmu_node_t) <= sizeof(mmu_node_t) + 1) {
        block->size = block->next - block - sizeof(mmu_node_t);
        return (void *)(block + 1);
    }

    mmu_node_t *next = (mmu_node_t *)((uint8_t *)block + size + sizeof(mmu_node_t));
    next->next = block->next;
    next->size = block->next - block - sizeof(mmu_node_t);
    next->is_free = 1;
    block->next = next;

    return (void *)(block + 1);
}

void _defragment_heap(bool kernel) {
    mmu_node_t *current = kernel ? mmu_k_head : mmu_head;
    while(current->next) {
        if(current->is_free && current->next->is_free) {
            current->size += current->next->size + sizeof(mmu_node_t);
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void mmu_free(void *ptr) {
    if(!ptr) return;

    bool kernel;
    if(ptr > (void *)heap && ptr < (void *)(heap + MMU_HEAP_SIZE))
        kernel = false;
    else if(ptr > (void *)k_heap && ptr < (void *)(k_heap + MMU_HEAP_SIZE))
        kernel = true;
    else return;

    mmu_node_t *block = (mmu_node_t *)ptr - 1;
    block->is_free = 1;

    _defragment_heap(kernel);
}