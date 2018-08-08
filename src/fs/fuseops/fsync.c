#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_fsync(const char *path, int _, struct fuse_file_info *fi)
{
    return 0;
}