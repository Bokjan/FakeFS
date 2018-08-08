#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_symlink(const char *target, const char *_linkpath)
{
    // the link file's mode should be rwxrwxrwx (0777)
    debug("ffs_symlink: linkpath=%s target=%s\n", _linkpath, target);
    char *linkpath = strdup(_linkpath);
    int spos = ffs_split_parent(linkpath);
    // construct entry
    ffs_entry_t e, ee;
    memset(&e, 0, sizeof(e));
    e.type = FFS_TYPE_SYMLINK;
    e.fileid = ffs_counter_increase();
    strcpy(e.filename, linkpath + spos + 1);
    // create and write the link file
    char *fn = ffs_path_by_id(e.fileid);
    FILE *fp = fopen(fn, "w");
    fwrite(target, strlen(target), 1, fp);
    fclose(fp);
    free(fn);
    // write the entry
    ffs_idpair_t dirid = ffs_findid(linkpath);
    fn = ffs_path_by_id(dirid.id);
    fp = fopen(fn, "r+");
    int c = 0;
    while(fread(&ee, sizeof(ee), 1, fp) == 1)
    {
        if(ee.filename[0] == '\0')
            break;
        ++c;
    }
    fseek(fp, c * sizeof(ffs_entry_t), SEEK_SET);
    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);
    free(fn);
    free(linkpath);
    return 0;
}