#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_release(const char *path, struct fuse_file_info *fi)
{
    int fd = ffs_fdmap_get(path);
    close(fd);
    ffs_fdmap_remove(path);
    return 0;
}