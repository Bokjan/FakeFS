#include "../def.h"
#include "../ffs.h"
#include "../util.h"
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/* FUSE won't move a file to nonexist dir */
int ffs_rename(const char *_from, const char *_to)
{
    int ret = 0;
    // debug("ffs_rename: p=%s,q=%s\n", _from, _to);
    char *from = strdup(_from);
    char *to   = strdup(_to);
    int fslashpos = ffs_split_parent(from);
    int tslashpos = ffs_split_parent(to);
    ffs_idpair_t fpdir = ffs_findid(from);
    ffs_idpair_t tpdir = ffs_findid(to);
    if(strcmp(from, to) == 0) // actual rename - same directory
    {
        int c = 0;
        ffs_entry_t e;
        char *fn = ffs_path_by_id(fpdir.id);
        FILE *fp = fopen(fn, "r+");
        while(fread(&e, sizeof(e), 1, fp) == 1)
        {
            if(strcmp(e.filename, from + fslashpos + 1) != 0)
                ++c;
            else
                break;
        }
        strcpy(e.filename, to + tslashpos + 1);
        fseek(fp, c * sizeof(ffs_entry_t), SEEK_SET);
        fwrite(&e, sizeof(e), 1, fp);
        fclose(fp);
        free(fn);
    }
    else // not the same directory
    {
        // check if a same file is already in the dest dir
        ffs_entry_t e;
        bool isdup = false;
        char *fn = ffs_path_by_id(tpdir.id);
        FILE *fp = fopen(fn, "r+");
        while(fread(&e, sizeof(e), 1, fp) == 1)
        {
            if(strcmp(e.filename, to + tslashpos + 1) == 0)
            {
                isdup = true;
                break;
            }
        }
        // if is_duplicated
        if(isdup)
        {
            ret = -EEXIST;
        }
        else
        {
            // read the original entry
            // and delete it
            int oc = 0;
            ffs_entry_t oe;
            char *ofn = ffs_path_by_id(fpdir.id);
            FILE *ofp = fopen(ofn, "r+");
            while(fread(&oe, sizeof(oe), 1, ofp) == 1)
            {
                if(strcmp(oe.filename, from + fslashpos + 1) == 0)
                    break;
                ++oc;
            }
            // debug("ffs_rename: oc=%d s1=%s s2=%s\n", oc, oe.filename, from + fslashpos);
            memcpy(&e, &oe, sizeof(ffs_entry_t));
            strcpy(e.filename, to + tslashpos + 1); // the new filename
            // fill back zeroes
            memset(&oe, 0, sizeof(oe));
            fseek(ofp, oc * sizeof(ffs_entry_t), SEEK_SET);
            fwrite(&oe, sizeof(oe), 1, ofp);
            fclose(ofp);
            free(ofn);
            // now `e` is the actual new entry struct
            // we'll find a space and put it in the dest entry book
            int c = 0;
            fseek(fp, 0, SEEK_SET);
            while(fread(&oe, sizeof(oe), 1, fp) == 1)
            {
                if(oe.filename[0] == '\0') // a `deleted` entry
                    break;
                ++c;
            }
            fseek(fp, c * sizeof(ffs_entry_t), SEEK_SET);
            fwrite(&e, sizeof(e), 1, fp);
        }
        fclose(fp);
        free(fn);
    }
    free(to);
    free(from);
    return ret;
}