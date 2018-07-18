#include "util.h"

char *ffs_root;

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