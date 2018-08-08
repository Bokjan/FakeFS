#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_utimens(const char *path, const struct timespec tv[2])
{
    int fd = ffs_actually_open(path, fi);
    futimens(fd, tv);
    close(fd);
    return 0;
}