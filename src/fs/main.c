#include "ffs.h"
#include "util.h"
#include <stdlib.h>

static struct fuse_operations ffs_operations = 
{
    .readdir   = ffs_readdir,
    .getattr   = ffs_getattr,
    .mkdir     = ffs_mkdir,
    .rmdir     = ffs_rmdir,
    .unlink    = ffs_rmdir, // temporarily, this one
    .rename    = ffs_rename,
    .chmod     = ffs_chmod,
    .chown     = ffs_chown,
    .utimens   = ffs_utimens,
    .statfs    = ffs_statfs,

    .create    = ffs_create,
    .open      = ffs_open,
    .release   = ffs_release,
    .read      = ffs_read,
    .write     = ffs_write,
    .flush     = ffs_flush,
    .fsync     = ffs_fsync,
    .truncate  = ffs_truncate,
    .ftruncate = ffs_ftruncate
};

int main(int argc, char *argv[])
{
    int ret;
    ffs_init(NULL);
    debug("%s\n", "run fuse_main...");
    ret = fuse_main(argc, argv, &ffs_operations, NULL);
    return ret;
}