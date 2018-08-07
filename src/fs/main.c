#include "ffs.h"
#include "util.h"
#include <stdlib.h>

static struct fuse_operations ffs_operations = 
{
    .readdir = ffs_readdir,
    .getattr = ffs_getattr,
    .mkdir   = ffs_mkdir
};

int main(int argc, char *argv[])
{
    int ret;
    ffs_init(NULL);
    debug("%s\n", "run fuse_main...");
    ret = fuse_main(argc, argv, &ffs_operations, NULL);
    return ret;
}