#ifndef FAKEFS_FFS_H
#define FAKEFS_FFS_H
#ifdef __cplusplus
extern "C" {
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
int ffs_chmod(const char *path, mode_t mode);
int ffs_chown(const char *path, uid_t uid, gid_t gid);
int ffs_utimens(const char *path, const struct timespec tv[2]);
int ffs_statfs(const char *path, struct statvfs *s);

int ffs_create(const char *path, mode_t mode, struct fuse_file_info *fi);
int ffs_open(const char *path, struct fuse_file_info *fi);
int ffs_release(const char *path, struct fuse_file_info *fi);
int ffs_read(const char *path, char *buf, 
    size_t count, off_t offset, struct fuse_file_info *fi);
int ffs_write(const char *path, const char *buf, 
    size_t count, off_t offset, struct fuse_file_info *fi);
int ffs_flush(const char *path, struct fuse_file_info *fi);
int ffs_fsync(const char *path, int _, struct fuse_file_info *fi);
int ffs_truncate(const char *path, off_t len);
int ffs_ftruncate(const char *path, off_t len, struct fuse_file_info *fi);
/* fuse_operations */

#ifdef __cplusplus
}
#endif
#endif
