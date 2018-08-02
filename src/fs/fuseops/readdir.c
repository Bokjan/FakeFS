#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int ffs_readdir(
    const char *path, void *buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info *fi)
{
    ffs_idpair_t dirid;
    if(strcmp("/", path) != 0)
        dirid = ffs_findid(path);
    if(dirid.id == -1 || dirid.type != FFS_TYPE_DIR)
        return -ENOENT;
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    char *p = ffs_path_by_id(dirid.id);
    FILE *fp = fopen(p, "r");
    ffs_entry_t entry;
    while(fread(&entry, sizeof(entry), 1, fp) != EOF)
    {
        struct stat est;
        char *epath = ffs_path_by_id(entry.fileid);
        stat(epath, &est);
        if(entry.type == FFS_TYPE_DIR)
            est.st_mode = S_IFDIR | (est.st_mode & 0777);
        filler(buf, entry.filename, &est, 0);
        free(epath);
    }
    fclose(fp);
    free(p);
    return 0;
}