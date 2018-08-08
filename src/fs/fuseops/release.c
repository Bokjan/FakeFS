#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_release(const char *path, struct fuse_file_info *fi)
{
    return 0;
}