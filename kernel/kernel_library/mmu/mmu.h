#ifndef __MMU_H
#define __MMU_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MMU_HEAP_SIZE 1024 * 1024 * 4 //4mb
typedef struct __attribute__((packed)) _mmu_node {
    size_t size;
    uint8_t is_free;
    struct _mmu_node *next;
} mmu_node_t;

extern uint8_t k_heap[MMU_HEAP_SIZE]__attribute__((aligned(4096)));
extern uint8_t heap[MMU_HEAP_SIZE]__attribute__((aligned(4096)));

void mmu_init(void);
void *mmu_allocate(size_t size, bool kernel);
void mmu_free(void *ptr);

#endif