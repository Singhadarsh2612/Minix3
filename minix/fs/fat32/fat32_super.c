#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minix/fsdriver.h>
#include "fat32.h"

#define FAT32_SIGNATURE 0xAA55

/* Read and parse the FAT32 boot sector */
int fat32_read_super(struct fat32_fs *fs, struct fsdriver *driver) {
    struct fat32_boot_sector bs;
    ssize_t bytes_read;

    /* Read the boot sector (first 512 bytes) */
    bytes_read = driver->read(0, &bs, sizeof(struct fat32_boot_sector));
    if (bytes_read != sizeof(struct fat32_boot_sector)) {
        printf("FAT32: Error reading boot sector\n");
        return -1;
    }

    /* Validate FAT32 signature */
    if (bs.signature != FAT32_SIGNATURE) {
        printf("FAT32: Invalid boot sector signature\n");
        return -1;
    }

    /* Check that it's FAT32 */
    if (bs.fat_size_16 != 0) {
        printf("FAT32: Not a valid FAT32 file system\n");
        return -1;
    }

    /* Store FAT32 file system metadata */
    fs->bytes_per_sector = bs.bytes_per_sector;
    fs->sectors_per_cluster = bs.sectors_per_cluster;
    fs->reserved_sectors = bs.reserved_sectors;
    fs->fat_count = bs.fat_count;
    fs->fat_size = bs.fat_size_32;
    fs->root_cluster = bs.root_cluster;
    fs->fsinfo_sector = bs.fsinfo_sector;
    fs->backup_boot_sector = bs.backup_boot_sector;

    printf("FAT32: Successfully read superblock\n");
    return 0;
}

/* Free FAT32 superblock resources */
void fat32_unmount(struct fat32_fs *fs) {
    if (fs) {
        free(fs);
        printf("FAT32: File system unmounted\n");
    }
}
