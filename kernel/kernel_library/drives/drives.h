#ifndef _DRIVES_
    #define _DRIVES_

    #define ATA_DATA_PORT          0x1F0
    #define ATA_ERROR_PORT         0x1F1
    #define ATA_SECTOR_COUNT_PORT  0x1F2
    #define ATA_SECTOR_NUMBER_PORT 0x1F3
    #define ATA_CYLINDER_LOW_PORT  0x1F4
    #define ATA_CYLINDER_HIGH_PORT 0x1F5
    #define ATA_DRIVE_HEAD_PORT    0x1F6
    #define ATA_COMMAND_PORT       0x1F7
    #define ATA_STATUS_PORT        0x1F7

    #define ATA_CMD_READ_SECTOR 0x20
    #define ATA_SR_BSY          0x80
    #define ATA_SR_DRQ          0x08

    #define SECTOR_SIZE 512

    #define OEM_ID "Basic OS"

    typedef struct {
        uint8_t  jump_instruction[3];
        char     oem_name[8];
        uint16_t bytes_per_sector;
        uint8_t  sectors_per_cluster;
        uint16_t reserved_sectors;
        uint8_t  number_of_fats;
        uint16_t max_root_dir_entries;
        uint16_t total_sectors_small;
        uint8_t  media_descriptor;
        uint16_t sectors_per_fat_16;
        uint16_t sectors_per_track;
        uint16_t number_of_heads;
        uint32_t hidden_sectors;
        uint32_t total_sectors_large;

        uint32_t sectors_per_fat_32;
        uint16_t extended_flags;
        uint16_t filesystem_version;
        uint32_t root_cluster_number;
        uint16_t filesystem_info_sector;
        uint16_t backup_boot_sector;
        uint8_t  reserved[12];
        uint8_t  drive_number;
        uint8_t  reserved_nt;
        uint8_t  extended_boot_signature;
        uint32_t volume_serial_number;
        char     volume_label[11];
        char     filesystem_type[8];
        uint8_t  boot_code[420];
        uint16_t boot_signature;
    } __attribute__((packed)) bpb_header_t;

    typedef struct {
        uint32_t lead_signature;
        uint8_t  reserved[480];
        uint32_t structure_signature;
        uint32_t free_cluster_count;
        uint32_t next_free_cluster;
        uint8_t  reserved2[12];
        uint32_t boot_signature;
    } __attribute__((packed)) fsinfo_header_t;

    typedef struct {
        uint8_t head;
        uint8_t sector;
        uint8_t cylinder;
    } __attribute__((packed)) chs_address_t;

    typedef struct {
        uint8_t status;
        chs_address_t chs_first;
        uint8_t type;
        chs_address_t chs_last;
        uint32_t first_lba;
        uint32_t sector_count;
    } __attribute__((packed)) partition_header_t;

    typedef struct {
        uint8_t boot_code[446];
        partition_header_t partitions[4];
        uint16_t boot_signature;
    } __attribute__((packed)) mbr_header_t;

    typedef struct {
        char     filename[11];
        uint8_t  attributes;
        uint8_t  reserved;
        uint8_t  creation_time_yap;
        uint16_t creation_time;
        uint16_t creation_date;
        uint16_t access_date;
        uint16_t cluster_high;
        uint32_t modification_time;
        uint16_t cluster_low;
        uint32_t filesize;
    } __attribute__((packed)) fat32_directory_t;

    typedef struct {
        char     file_name[12];
        uint32_t first_cluster;
        size_t   file_size;
    } file_t;

    mbr_header_t mbr;
    
    file_t dirs[128];
    uint64_t dir_counter = 0;

    void drive_init(mbr_header_t *mbr_ptr);
    void drive_readsector(uint32_t lba, uint8_t *buffer);
    file_t drive_getfile(char *file);
    void drive_readfile(file_t file, uint8_t *buffer, uint32_t buf_size);
    #include "./fs.c"
#endif