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
int ffs_readdir(
    const char *path, void *buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info *fi);
int ffs_getattr(const char *path, struct stat *stbuf);
int ffs_mkdir(const char *path, mode_t mode);

#ifdef __cplusplus
}
#endif
#endif
