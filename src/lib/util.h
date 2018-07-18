#ifndef FAKEFS_UTIL_H
#define FAKEFS_UTIL_H

#include <stdio.h>

extern char *ffs_root;

int ffsi_get_file_size(FILE *fp);

#endif