# Implementation of FAT32 File System and Scheduling Algorithm Change in MINIX 3

## Overview
This document details the modifications made to the MINIX 3 operating system to support the FAT32 file system and the transition from a priority-based scheduling algorithm to a round-robin scheduler. Each implementation is discussed separately for clarity and maintainability.

---

## **FAT32 File System Implementation**

### **Introduction**
The FAT32 file system was integrated into MINIX 3 to support a widely used, lightweight file system. This required implementing the necessary structures, read/write mechanisms, and directory management functionalities.

### **Changes Made**

1. **New Source Files Added:**
   - `fs/fat32/fat32.c` - Core FAT32 functionality
   - `fs/fat32/fat32_super.c` - Superblock handling
   - `fs/fat32/fat32_dir.c` - Directory operations
   - `fs/fat32/fat32_rdwt.c` - Read/write functionality
   - `fs/fat32/fat32.h` - Header file containing FAT32 structures and prototypes

2. **Modifications in MINIX Build System:**
   - Updated `fs/Makefile` to include FAT32 source files.
   - Modified `fs/main.c` to initialize the FAT32 file system.
   - Registered FAT32 under the `fs/fat32` directory in `fs/table.c`.

3. **Implemented FAT32 Functionality:**
   - Boot sector parsing and validation.
   - FAT table handling for cluster chain management.
   - Directory entry management (reading and writing file metadata).
   - File read/write support.

### **Compilation and Testing**
To ensure seamless integration, the FAT32 file system was tested with:
   - Creating and listing directories
   - Reading and writing files
   - Checking FAT table consistency

---

## **Transition from Priority-Based to Round-Robin Scheduling**

### **Introduction**
MINIX 3 originally used a **priority-based** scheduling algorithm. This was replaced with a **round-robin scheduler** to ensure fair CPU time distribution among processes.

### **Changes Made**

1. **Modified Scheduler Implementation:**
   - The existing priority-based logic was removed from `kernel/sched.c`.
   - A round-robin time-slice mechanism was implemented.

2. **Code Changes:**
   - Edited `kernel/proc.c` to reset process quantum after each execution.
   - Changed `kernel/sched.c` to select the next process based on **time slice expiration** rather than priority.
   - Updated `kernel/proc.h` to store **time quantum values**.

3. **Testing:**
   - Verified round-robin execution by running multiple CPU-intensive tasks.
   - Ensured that no process starves due to scheduling bias.

---

## **Conclusion**
The above modifications enable MINIX 3 to support FAT32 as a file system while ensuring fair CPU scheduling via the round-robin algorithm. These changes improve usability and responsiveness, making MINIX 3 more practical for various applications.

For further details, refer to the modified source files in the respective directories.

---

### **Author**
Adarsh Kumar Singh

### **Repository**
[GitHub: Minix3](https://github.com/Singhadarsh2612/Minix3)

