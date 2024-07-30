void drive_poll(void) {
    while (inb(ATA_STATUS_PORT) & ATA_SR_BSY);
    while (!(inb(ATA_STATUS_PORT) & ATA_SR_DRQ));
}

void drive_readsector(uint32_t lba, uint8_t *buffer) {
    outb(ATA_DRIVE_HEAD_PORT, 0xE0 | ((lba >> 24) & 0x0F));  // Drive 0 and LBA
    outb(ATA_SECTOR_COUNT_PORT, 1);  // Sector count
    outb(ATA_SECTOR_NUMBER_PORT, (uint8_t) lba);  // LBA low
    outb(ATA_CYLINDER_LOW_PORT, (uint8_t)(lba >> 8));  // LBA mid
    outb(ATA_CYLINDER_HIGH_PORT, (uint8_t)(lba >> 16));  // LBA high
    outb(ATA_COMMAND_PORT, ATA_CMD_READ_SECTOR);  // Send read command

    drive_poll();

    for (int i = 0; i < 256; i++)
        ((uint16_t *)buffer)[i] = inw(ATA_DATA_PORT);
}

file_t drive_getfile(char *file) {
    for(uint64_t i = 0; i < dir_counter; i++)
        if(string_compare(file, dirs[i].file_name) == true)
            return dirs[i];

    return (file_t) {
        .file_name = {
            '\0'
        },
        .first_cluster = 0,
        .file_size = 0
    };
}

void drive_readfile(file_t file, uint8_t *buffer, uint32_t buf_size) {
    uint32_t sector = 5198 + file.first_cluster;
    uint8_t *ptr = buffer;

    for(size_t i = 0; i < buf_size / 512; i++) {
        ptr = buffer + i * 512;
        drive_readsector(sector, ptr);
        sector++;
    }
}

void drive_init(mbr_header_t *mbr_ptr) {
    drive_readsector(0, (uint8_t *)mbr_ptr);

    uint8_t bpb_buffer[512];
    bpb_header_t *bpb = (bpb_header_t *)bpb_buffer;
    drive_readsector(mbr_ptr->partitions[0].first_lba, bpb_buffer);

    uint8_t buffer[512];
    drive_readsector(5168 + bpb->reserved_sectors, buffer);
    fat32_directory_t *dir = (fat32_directory_t *)buffer;
    
    for(size_t i = 0; dir[i].filename[0]; i++) {
        if(dir[i].attributes == 0x0f || dir[i].attributes & 0x10)
            continue;
        
        dirs[dir_counter] = (file_t) {
            .file_name = {
                "            "
            },
            .first_cluster = dir[i].cluster_low | (dir[i].cluster_high << 16),
            .file_size = dir[i].filesize
        };

        for(int j = 0; j < 11; j++)
            dirs[dir_counter].file_name[j] = dir[i].filename[j];
        dirs[dir_counter].file_name[11] = '\0';
        dir_counter++;
    }
}