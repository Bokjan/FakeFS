#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int ffs_getattr(const char *path, struct stat *stbuf)
{
    ffs_idpair_t fileid = ffs_findid(path);
    if(fileid.id == -1)
        return -ENOENT;
    struct stat sb;
    memset(&sb, 0, sizeof(struct stat));
    memset(stbuf, 0, sizeof(struct stat));
    char *p = ffs_path_by_id(fileid.id);
    stat(p, &sb);
    if(fileid.type == FFS_TYPE_DIR)
    {
        stbuf->st_mode = (sb.st_mode & 0777) | S_IFDIR;
        stbuf->st_nlink = sb.st_size / sizeof(ffs_entry_t) + 1;
        stbuf->st_uid = sb.st_uid;
        stbuf->st_gid = sb.st_gid;
        stbuf->st_size = 4096;
        stbuf->st_atime = sb.st_atime;
        stbuf->st_mtime = sb.st_mtime;
        stbuf->st_ctime = sb.st_ctime;
    }
    else
    {
        memcpy(stbuf, &sb, sizeof(struct stat));
    }
    free(p);
    return 0;
}
