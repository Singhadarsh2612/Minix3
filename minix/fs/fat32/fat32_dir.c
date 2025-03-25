#include "fat32.h"
#include <minix/fsdriver.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

#define FAT32_DIR_ENTRY_SIZE 32  // Each directory entry is 32 bytes
#define FAT32_EOC 0x0FFFFFF8      // End of Cluster marker

/* Reads a directory from a given cluster */
int fat32_read_dir(struct fat32_fs *fs, uint32_t cluster, struct fat32_dir_entry *entries, size_t max_entries) {
    uint32_t sector, offset, cluster_size;
    size_t entry_count = 0;
    struct fat32_dir_entry *dir_entry;

    if (cluster == 0) {
        return -1;  // Invalid cluster
    }

    cluster_size = fs->sectors_per_cluster * fs->bytes_per_sector;

    while (cluster < FAT32_EOC) {
        sector = fat32_cluster_to_sector(fs, cluster);
        offset = 0;

        while (offset < cluster_size && entry_count < max_entries) {
            dir_entry = (struct fat32_dir_entry *)(fs->buffer + offset);

            if (dir_entry->name[0] == 0x00) {
                return entry_count;  // No more entries
            }
            if (dir_entry->name[0] != 0xE5) {  // Ignore deleted entries
                memcpy(&entries[entry_count], dir_entry, FAT32_DIR_ENTRY_SIZE);
                entry_count++;
            }

            offset += FAT32_DIR_ENTRY_SIZE;
        }

        cluster = fat32_get_next_cluster(fs, cluster);
    }

    return entry_count;
}

/* Searches for a file inside a directory */
int fat32_find_entry(struct fat32_fs *fs, uint32_t dir_cluster, const char *filename, struct fat32_dir_entry *result) {
    struct fat32_dir_entry entries[128];
    int num_entries = fat32_read_dir(fs, dir_cluster, entries, 128);

    for (int i = 0; i < num_entries; i++) {
        if (strncmp((char *)entries[i].name, filename, 11) == 0) {  // FAT32 names are 11 bytes
            memcpy(result, &entries[i], sizeof(struct fat32_dir_entry));
            return 0;
        }
    }
    return -1;  // File not found
}
