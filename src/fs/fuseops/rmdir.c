#include "../def.h"
#include "../ffs.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_rmdir(const char *_path)
{
    char *path = strdup(_path);
    /* Don't care about the parent dir's existence - FUSE already did */
    int slashpos = ffs_split_parent(path);
    char *dirname = path + slashpos + 1;
    ffs_idpair_t parid = ffs_findid(path);
    ffs_idpair_t dirid = ffs_findid(_path);
    /* Delete _path's entry file */
    char *fn = ffs_path_by_id(dirid.id);
    unlink(fn);
    free(fn);
    /* Mark this entry as deleted in parent's entry book */
    fn = ffs_path_by_id(parid.id);
    FILE *fp = fopen(fn, "r+");
    int pos = 0;
    ffs_entry_t e;
    while(fread(&e, sizeof(e), 1, fp) == 1)
    {
        if(strcmp(dirname, e.filename) != 0) // not found
        {
            ++pos;
            continue;
        }
        memset(&e, 0, sizeof(e));
        fseek(fp, pos * sizeof(ffs_entry_t), SEEK_SET);
        fwrite(&e, sizeof(e), 1, fp);
        break;
    }
    fclose(fp);
    free(fn);
    free(path);
    return 0;
}