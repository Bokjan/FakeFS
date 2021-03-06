#include "def.h"
#include "util.h"
#include <fuse.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *ffs_root;
size_t ffs_root_len;
char *ffs_counter_path;
pthread_mutex_t ffs_counter_mutex;

void debug(const char *fmt, ...)
{
    static FILE *fp = NULL;
    if(fp == NULL)
        fp = fopen(DEBUG_FILE, DEBUG_MODE);
    fprintf(fp, "pid=%d ", getpid());
    va_list ap;
    va_start(ap, fmt);
    vfprintf(fp, fmt, ap);
    va_end(ap);
    fflush(fp);
}

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
        while(fread(&entry, sizeof(entry), 1, fp) == 1)
        {
            if(strcmp(entry.filename, s) != 0)
                continue;
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
    return ret;
}

int ffs_counter_value(void)
{
    int ret = -1;
    pthread_mutex_lock(&ffs_counter_mutex);
    FILE *fp = fopen(ffs_counter_path, "r");
    fread(&ret, sizeof(ret), 1, fp);
    fclose(fp);
    pthread_mutex_unlock(&ffs_counter_mutex);
    return ret;
}

int ffs_counter_increase(void)
{
    int ret = -1;
    pthread_mutex_lock(&ffs_counter_mutex);
    FILE *fp = fopen(ffs_counter_path, "r+");
    fread(&ret, sizeof(ret), 1, fp);
    ++ret;
    fseek(fp, 0, SEEK_SET);
    fwrite(&ret, sizeof(ret), 1, fp);
    fclose(fp);
    pthread_mutex_unlock(&ffs_counter_mutex);
    return ret;
}

/* Change the last slash(`/`) to '\0' */
int ffs_split_parent(char *path)
{
    int len = strlen(path);
    for(int i = len - 1; i >= 0; --i)
    {
        if(path[i] == '/')
        {
            path[i] = '\0';
            return i;
        }
    }
    return len - 1;
}

int ffs_actually_open(const char *_path, struct fuse_file_info *fi)
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
    free(fn);
    free(path);
    return fd;
}