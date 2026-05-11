#include "./mmu.h"

uint8_t k_heap[MMU_HEAP_SIZE]__attribute__((aligned(4096)));
uint8_t heap[MMU_HEAP_SIZE]__attribute__((aligned(4096)));

mmu_node_t *mmu_k_head = (mmu_node_t *)k_heap;
mmu_node_t *mmu_head = (mmu_node_t *)heap;

void mmu_init(void) {
    mmu_head = (mmu_node_t *)heap;
    mmu_head->size = MMU_HEAP_SIZE - sizeof(mmu_node_t);
    mmu_head->is_free = 1;
    mmu_head->next = NULL;
    
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
    if (!size) return NULL;

    mmu_node_t *block = _get_first_free_block(size, kernel);
    if (!block) return NULL;

    if (block->size > size + sizeof(mmu_node_t)) {
        // Split the block
        mmu_node_t *new_block = (mmu_node_t *)((uint8_t *)block + sizeof(mmu_node_t) + size);
        new_block->size = block->size - size - sizeof(mmu_node_t);
        new_block->is_free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }

    block->is_free = 0;
    return (void *)(block + 1);
}

void _defragment_heap(bool kernel) {
    mmu_node_t *current = kernel ? mmu_k_head : mmu_head;

    while(current && current->next)
        if(current->is_free && current->next->is_free) {
            current->size += current->next->size + sizeof(mmu_node_t);
            current->next = current->next->next;
        }
        else
            current = current->next;
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