void _syscall_memory_allocate(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    has_return = true;
    return_value = (uint32_t)mmu_allocate(eax & 0x0000ffff, false);
}

void _syscall_memory_free(uint32_t eax, uint32_t ebx, uint32_t ecx) {
    mmu_free((void *)ebx);
}

_calls memory_calls[] = {
    _syscall_memory_allocate,
    _syscall_memory_free
}