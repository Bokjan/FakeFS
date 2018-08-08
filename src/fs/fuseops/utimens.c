#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_utimens(const char *path, const struct timespec tv[2])
{
    int fd = ffs_fdmap_get(path);
    futimens(fd, tv);
    return 0;
}