#ifndef _MMU_
    #define _MMU_
    #define MMU_HEAP_SIZE 1024 * 1024 * 4 //4mb
    typedef struct __attribute__((packed)) _mmu_node {
        size_t size;
        uint8_t is_free;
        struct _mmu_node *next;
    } mmu_node_t;

    static uint8_t k_heap[MMU_HEAP_SIZE]__attribute__((aligned(4096)));
    static uint8_t heap[MMU_HEAP_SIZE]__attribute__((aligned(4096)));
    mmu_node_t *mmu_k_head = (mmu_node_t *)k_heap;
    mmu_node_t *mmu_head = (mmu_node_t *)heap;

    void mmu_init(void);
    void *mmu_allocate(size_t size, bool kernel);
    void mmu_free(void *ptr);

    #include "mmu.c"
#endif