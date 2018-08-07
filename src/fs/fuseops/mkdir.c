#include "../def.h"
#include "../ffs.h"
#include "../util.h"
#include <string.h>

int ffs_mkdir(const char *_path, mode_t mode)
{
    char *path = strdup(_path);
    /* Don't care about the parent dir's existence - FUSE already did */
    int slashpos = ffs_split_parent(path);
    char *dirname = path + slashpos + 1;
    ffs_idpair_t parid = ffs_findid(path);
    int dirid = ffs_counter_increase();
    /* Create file<id> file */
    char *fn = ffs_path_by_id(dirid);
    FILE *fp = fopen(fn, "w");
    fclose(fp);
    mode = mode & (~S_IFDIR); // file<dirid> is a file, not real directory
    chmod(fn, mode);
    free(fn);
    /* Add dir entry */
    ffs_entry_t entry;
    memset(&entry, 0, sizeof(entry));
    entry.type = FFS_TYPE_DIR;
    entry.fileid = dirid;
    strcpy(entry.filename, dirname);
    fn = ffs_path_by_id(parid.id);

    fp = fopen(fn, "r+");
    /* Find a `deleted` entry if exists */
    ffs_entry_t e;
    int poscount = 0;
    while(fread(&e, sizeof(e), 1, fp) == 1)
    {
        if(e.filename[0] == '\0')
            break;
        ++poscount; // A_I after break, to simplify the calc
    }
    fseek(fp, poscount * sizeof(ffs_entry_t), SEEK_SET);
    fwrite(&entry, sizeof(entry), 1, fp);
    fclose(fp);

    free(fn);
    free(path);
    return 0;
}