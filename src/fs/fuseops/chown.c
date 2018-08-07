#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <unistd.h>

int ffs_chown(const char *path, uid_t uid, gid_t gid)
{
    ffs_idpair_t id = ffs_findid(path);
    char *fn = ffs_path_by_id(id.id);
    chown(fn, uid, gid);
    free(fn);
    return 0;
}