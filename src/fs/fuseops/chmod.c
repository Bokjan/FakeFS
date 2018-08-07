#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_chmod(const char *path, mode_t mode)
{
    ffs_idpair_t id = ffs_findid(path);
    char *fn = ffs_path_by_id(id.id);
    chmod(fn, mode);
    free(fn);
    return 0;
}