# Makefile for FAT32 File System (FAT32)
PROG=	fat32
SRCS=	cache.c link.c \
	mount.c misc.c open.c protect.c read.c \
	stadir.c stats.c table.c time.c utility.c \
	write.c inode.c main.c path.c super.c \
	fat32.c fat32_rdwt.c fat32_dir.c fat32_super.c

DPADD+=	${LIBMINIXFS} ${LIBFSDRIVER} ${LIBBDEV} ${LIBSYS}
LDADD+= -lminixfs -lfsdriver -lbdev -lsys

CPPFLAGS+= -DDEFAULT_NR_BUFS=1024

.include <minix.service.mk>
