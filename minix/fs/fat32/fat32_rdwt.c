#include "fat32.h"
#include <minix/fsdriver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Read a file from the FAT32 filesystem */
ssize_t fat32_read_file(struct fat32_fs *fs, uint32_t start_cluster, void *buffer, size_t size) {
    size_t bytes_read = 0;
    uint32_t cluster = start_cluster;
    uint8_t *buf = (uint8_t *)buffer;

    while (size > 0 && cluster < 0x0FFFFFF8) { // Valid FAT32 cluster range
        uint32_t sector = fat32_cluster_to_sector(fs, cluster);
        if (sector == 0) {
            return -1;  // Invalid sector
        }

        // Read the entire cluster
        if (fs_read_sector(fs, sector, buf) < 0) {
            return -1; // Error reading sector
        }

        size_t to_read = (size < fs->bytes_per_sector) ? size : fs->bytes_per_sector;
        buf += to_read;
        size -= to_read;
        bytes_read += to_read;

        // Get the next cluster from FAT
        cluster = fat32_get_next_cluster(fs, cluster);
    }

    return bytes_read;
}

/* Write a file to the FAT32 filesystem */
ssize_t fat32_write_file(struct fat32_fs *fs, uint32_t start_cluster, const void *buffer, size_t size) {
    size_t bytes_written = 0;
    uint32_t cluster = start_cluster;
    const uint8_t *buf = (const uint8_t *)buffer;

    while (size > 0) {
        uint32_t sector = fat32_cluster_to_sector(fs, cluster);
        if (sector == 0) {
            return -1;  // Invalid sector
        }

        // Write the entire cluster
        if (fs_write_sector(fs, sector, buf) < 0) {
            return -1; // Error writing sector
        }

        size_t to_write = (size < fs->bytes_per_sector) ? size : fs->bytes_per_sector;
        buf += to_write;
        size -= to_write;
        bytes_written += to_write;

        // Get the next cluster or allocate a new one if necessary
        uint32_t next_cluster = fat32_get_next_cluster(fs, cluster);
        if (next_cluster >= 0x0FFFFFF8) { // End of chain
            next_cluster = fat32_allocate_cluster(fs);
            if (next_cluster == 0) {
                return -1; // No free space
            }
            // Update the FAT entry
            fat32_set_next_cluster(fs, cluster, next_cluster);
        }

        cluster = next_cluster;
    }

    return bytes_written;
}
