#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_truncate(const char *path, off_t len)
{
    int ret;
    ffs_idpair_t id = ffs_findid(path);
    char *fn = ffs_path_by_id(id.id);
    ret = truncate(fn, len);
    free(fn);
    return ret;
}