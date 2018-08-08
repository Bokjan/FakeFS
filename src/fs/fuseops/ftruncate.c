#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_ftruncate(const char *path, off_t len, struct fuse_file_info *fi)
{
    return 0;
}