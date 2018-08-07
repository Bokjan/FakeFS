#ifndef FAKEFS_UTIL_H
#define FAKEFS_UTIL_H

#include <stdio.h>
#include <stdint.h>

extern char *ffs_root;
extern size_t ffs_root_len;

struct ffs_idpair
{
    int id, type;
};
typedef struct ffs_idpair ffs_idpair_t;

int ffsi_get_file_size(FILE *fp);
char* ffs_path_by_id(uint32_t id);
ffs_idpair_t ffs_findid(const char *path);

#define DEBUG_FILE "/tmp/ffs/debug.log"
#define DEBUG_MODE "w"
void debug(const char *fmt, ...);

#endif