#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

#define FAT32_NAME_LENGTH 11

/* FAT32 Directory Entry Structure */
struct fat32_dir_entry {
    uint8_t name[FAT32_NAME_LENGTH];  // 8.3 filename
    uint8_t attr;                     // File attributes
    uint8_t reserved;                  // Reserved
    uint8_t creation_time_tenth;        // Creation time (tenths of second)
    uint16_t creation_time;             // Creation time
    uint16_t creation_date;             // Creation date
    uint16_t last_access_date;          // Last access date
    uint16_t first_cluster_high;        // High 16 bits of first cluster
    uint16_t last_modified_time;        // Last modified time
    uint16_t last_modified_date;        // Last modified date
    uint16_t first_cluster_low;         // Low 16 bits of first cluster
    uint32_t file_size;                 // File size in bytes
};

/* FAT32 File System Structure */
struct fat32_fs {
    uint32_t sectors_per_cluster;
    uint32_t bytes_per_sector;
    uint8_t buffer[4096]; // Buffer for reading sectors
};

/* Function Prototypes */
int fat32_read_dir(struct fat32_fs *fs, uint32_t cluster, struct fat32_dir_entry *entries, size_t max_entries);
int fat32_find_entry(struct fat32_fs *fs, uint32_t dir_cluster, const char *filename, struct fat32_dir_entry *result);
uint32_t fat32_cluster_to_sector(struct fat32_fs *fs, uint32_t cluster);
uint32_t fat32_get_next_cluster(struct fat32_fs *fs, uint32_t cluster);

#endif /* FAT32_H */
