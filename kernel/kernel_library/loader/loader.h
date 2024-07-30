#ifndef _LOADER_
    #define _LOADER_

    #define EI_NIDENT 16

    typedef struct {
        unsigned char e_ident[EI_NIDENT]; // Magic number and other info
        uint16_t e_type;                  // Object file type
        uint16_t e_machine;               // Architecture
        uint32_t e_version;               // Object file version
        uint32_t e_entry;                 // Entry point virtual address
        uint32_t e_phoff;                 // Program header table file offset
        uint32_t e_shoff;                 // Section header table file offset
        uint32_t e_flags;                 // Processor-specific flags
        uint16_t e_ehsize;                // ELF header size in bytes
        uint16_t e_phentsize;             // Program header table entry size
        uint16_t e_phnum;                 // Program header table entry count
        uint16_t e_shentsize;             // Section header table entry size
        uint16_t e_shnum;                 // Section header table entry count
        uint16_t e_shstrndx;              // Section header string table index
    } elf_header_t;

    typedef void (*entry_point_t)(void);

    void binary_execute(uint8_t *buffer, size_t length);

    #include "./loader.c"
#endif