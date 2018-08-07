#ifndef FAKEFS_UTIL_H
#define FAKEFS_UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

extern char *ffs_root;
extern size_t ffs_root_len;
extern char *ffs_counter_path;
extern pthread_mutex_t ffs_counter_mutex;

struct ffs_idpair
{
    int id, type;
};
typedef struct ffs_idpair ffs_idpair_t;

int ffsi_get_file_size(FILE *fp);
char* ffs_path_by_id(uint32_t id);
ffs_idpair_t ffs_findid(const char *path);
int ffs_counter_value(void);
int ffs_counter_increase(void);

#define DEBUG_FILE "/tmp/ffs/debug.log"
#define DEBUG_MODE "w"
void debug(const char *fmt, ...);

#endif