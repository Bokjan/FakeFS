#include "ffs.h"
#include "util.h"
#include <stdlib.h>

static struct fuse_operations ffs_operations = 
{
    .readdir = ffs_readdir,
    .getattr = ffs_getattr,
    .mkdir   = ffs_mkdir,
    .rmdir   = ffs_rmdir,
    .unlink  = ffs_rmdir, // temporarily, this one
    .rename  = ffs_rename,
    .chmod   = ffs_chmod,
    .chown   = ffs_chown,

    .create  = ffs_create
};

int main(int argc, char *argv[])
{
    int ret;
    ffs_init(NULL);
    debug("%s\n", "run fuse_main...");
    ret = fuse_main(argc, argv, &ffs_operations, NULL);
    return ret;
}