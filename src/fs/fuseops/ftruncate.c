#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_ftruncate(const char *path, off_t len, struct fuse_file_info *fi)
{
    int ret;
    int fd = ffs_fdmap_get(path);
    ret = ftruncate(fd, len);
    return ret;
}