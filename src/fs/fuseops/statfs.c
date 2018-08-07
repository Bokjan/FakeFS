#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>

int ffs_statfs(const char *path, struct statvfs *s)
{
    ffs_idpair_t id = ffs_findid(path);
    char *fn = ffs_path_by_id(id.id);
    statvfs(fn, s);
    free(fn);
    return 0;
}