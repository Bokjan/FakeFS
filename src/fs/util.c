#include "def.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

char *ffs_root;
size_t ffs_root_len;

int ffsi_get_file_size(FILE *fp)
{
    if(fp == NULL)
        return -1;
    int now = ftell(fp);
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, now);
    return size;
}

char* ffs_path_by_id(uint32_t id)
{
    char *ret = (char*)malloc(ffs_root_len + 16);
    sprintf(ret, "%sfile%u", ffs_root, id);
    return ret;
}

ffs_idpair_t ffs_findid(const char *path)
{
    int parentid = 0, lastparentid = 0;
    int totaldircount = 0, dircount = 1;
    int pathlen = strlen(path);
    ffs_idpair_t ret = { .id = -1, .type = FFS_TYPE_DIR };
    char *p = strdup(path);
    for(int i = 0; i < pathlen; ++i)
        if(path[i] == '/')
            ++totaldircount;
    for(char *s = strtok(p, "/"); s != NULL && dircount <= totaldircount; s = strtok(NULL, "/"), ++dircount)
    {
        char *parentidpath = ffs_path_by_id(parentid);
        FILE *fp = fopen(parentidpath, "r");
        ffs_entry_t entry;
        while(fread(&entry, sizeof(entry), 1, fp) != EOF)
        {
            if(strcmp(entry.filename, s) != 0)
                continue;
            // fprintf(stderr, "entry: %s %d %d\n", entry.filename, entry.fileid, entry.type);
            parentid = entry.fileid;
            ret.type = entry.type;
            break;
        }
        fclose(fp);
        free(parentidpath);
        if(entry.type != FFS_TYPE_DIR && dircount != totaldircount)
            goto RETURN;
        if(parentid == lastparentid)
            goto RETURN;
        lastparentid = parentid;
    }
    ret.id = parentid;
RETURN:
    free(p);
    // fprintf(stderr, "==FINDID==\n%s ID=%d TYPE=%d\n==========\n", path, ret.id, ret.type);  
    return ret;
}