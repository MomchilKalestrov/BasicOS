#ifndef _PAGING_
    #define _PAGING_

    #define TABLES 9

    typedef struct {
        uint32_t entries[1024] __attribute__((aligned(4096)));
    } page_table_t;

    uint32_t page_directory[1024] __attribute__((aligned(4096)));
    page_table_t page_tables[TABLES];

    #include "./paging.c"
#endif