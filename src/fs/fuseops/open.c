#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_open(const char *_path, struct fuse_file_info *fi)
{
    char *path = strdup(_path);
    int slashpos = ffs_split_parent(path);
    ffs_idpair_t parid = ffs_findid(path);
    char *fn = ffs_path_by_id(parid.id);
    FILE *fp = fopen(fn, "r");
    ffs_entry_t entry;
    while(fread(&entry, sizeof(entry), 1, fp) == 1)
        if(strcmp(entry.filename, path + slashpos + 1) == 0)
            break;
    fclose(fp);
    free(fn);
    fn = ffs_path_by_id(entry.fileid);
    int fd = open(fn, fi->flags);
    close(fd);
    free(fn);
    free(path);
    return 0;
}