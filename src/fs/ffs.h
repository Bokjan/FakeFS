#ifndef FAKEFS_FFS_H
#define FAKEFS_FFS_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <fuse.h>
#include <stdio.h>

#include "def.h"

int ffs_init(const char *conf);

/* fuse_operations */
int ffs_readdir(
    const char *path, void *buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info *fi);
int ffs_getattr(const char *path, struct stat *stbuf);
int ffs_mkdir(const char *path, mode_t mode);
int ffs_rmdir(const char *path);
int ffs_unlink(const char *path);
int ffs_rename(const char *from, const char *to);
/* fuse_operations */

#ifdef __cplusplus
}
#endif
#endif
