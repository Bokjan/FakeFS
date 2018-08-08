#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_readlink(const char *path, char *buf, size_t maxlen)
{
    ffs_idpair_t id = ffs_findid(path);
    char *fn = ffs_path_by_id(id.id);
    FILE *fp = fopen(fn, "r");
    int len = fread(buf, 1, maxlen - 1, fp);
    buf[len] = '\0';
    // debug("ffs_readlink: path=%s maxlen=%u fn(actual)=%s buf=%s\n", path, maxlen, fn, buf);
    fclose(fp);
    free(fn);
    return 0;
}