#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minix/fsdriver.h>
#include "fat32.h"

/* FAT32 file system structure */
struct fat32_fs fat32_fs;

/* File system operations */
static struct fsdriver fat32_fsdriver = {
    .f_mount   = fat32_mount,
    .f_unmount = fat32_unmount,
    .f_lookup  = fat32_lookup,
    .f_getdents = fat32_getdents,
    .f_read    = fat32_read,
    .f_write   = fat32_write,
};

/* Mount the FAT32 file system */
int fat32_mount(dev_t dev, struct fsdriver *driver) {
    printf("FAT32: Mounting file system...\n");

    /* Read the superblock */
    if (fat32_read_super(&fat32_fs, driver) != 0) {
        printf("FAT32: Failed to read superblock\n");
        return -1;
    }

    /* Initialize FAT cache (if needed) */
    printf("FAT32: File system mounted successfully\n");
    return 0;
}

/* Unmount the FAT32 file system */
void fat32_unmount(void) {
    fat32_unmount(&fat32_fs);
}

/* Lookup a file/directory */
int fat32_lookup(struct inode *parent, char *name, struct inode *result) {
    printf("FAT32: Lookup for '%s'\n", name);
    return fat32_find_entry(&fat32_fs, parent->i_num, name, result);
}

/* Read directory entries */
int fat32_getdents(struct inode *dir, struct dirent *entries, size_t max_entries) {
    printf("FAT32: Reading directory entries\n");
    return fat32_read_dir(&fat32_fs, dir->i_num, entries, max_entries);
}

/* Read file contents */
ssize_t fat32_read(struct inode *inode, void *buf, size_t size, off_t offset) {
    printf("FAT32: Reading file (inode: %d, offset: %ld, size: %zu)\n", inode->i_num, offset, size);
    return fat32_read_file(&fat32_fs, inode->i_num, buf, size, offset);
}

/* Write to a file */
ssize_t fat32_write(struct inode *inode, const void *buf, size_t size, off_t offset) {
    printf("FAT32: Writing file (inode: %d, offset: %ld, size: %zu)\n", inode->i_num, offset, size);
    return fat32_write_file(&fat32_fs, inode->i_num, buf, size, offset);
}

/* Register FAT32 file system driver */
int main(void) {
    printf("FAT32: Registering file system driver...\n");
    fsdriver_register(&fat32_fsdriver);
    return 0;
}
