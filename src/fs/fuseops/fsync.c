#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_fsync(const char *path, int _, struct fuse_file_info *fi)
{
    int ret;
    int fd = ffs_fdmap_get(path);
    ret = fsync(fd);
    return ret;
}