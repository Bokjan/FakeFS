#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>

int ffs_create(const char *_path, mode_t mode, struct fuse_file_info *fi)
{
    char *path = strdup(_path);
    int slashpos = ffs_split_parent(path);
    ffs_idpair_t parid = ffs_findid(path);
    // create the actual file
    int newid = ffs_counter_increase();
    char *fn = ffs_path_by_id(newid);
    creat(fn, mode);
    free(fn);
    // add entry
    int c = 0;
    ffs_entry_t entry;
    fn = ffs_path_by_id(parid.id);
    FILE *fp = fopen(fn, "r+");
    while(fread(&entry, sizeof(entry), 1, fp) == 1)
    {
        if(entry.filename[0] == '\0')
            break;
        ++c;
    }
    memset(&entry, 0, sizeof(entry));
    entry.fileid = newid;
    strcpy(entry.filename, path + slashpos + 1);
    fseek(fp, c * sizeof(ffs_entry_t), SEEK_SET);
    fwrite(&entry, sizeof(entry), 1, fp);
    fclose(fp);
    free(fn);
    free(path);
    return 0;
}