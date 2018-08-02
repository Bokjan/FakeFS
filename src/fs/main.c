#include "ffs.h"
#include "util.h"
#include <stdlib.h>

static struct fuse_operations ffs_operations = 
{
    .readdir = ffs_readdir,
    .getattr = ffs_getattr,
};

int main(int argc, char *argv[])
{
    int ret;
    ffs_init(NULL);
    ret = fuse_main(argc, argv, &ffs_operations, NULL);
    return ret;
    // ffs_idpair_t id;
    // id = ffs_findid("/");
    // printf("%d %d\n", id.id, id.type);
}