#ifndef FAKEFS_DEF_H
#define FAKEFS_DEF_H
#ifdef __cplusplus
extern "C" {
#endif

/*
Entry structure:
    4 B    |    4 B    |     256 B    |
File or Dir|  File ID  | File/Dir Name|

If `Name` has 256 0x0, 
then this entry is marked as deleted.

*/

#include <stdint.h>

#define FILEID_LEN   (4)
#define FILENAME_LEN (256)
#define FFS_TYPE_FILE 0
#define FFS_TYPE_DIR  1

#define ROOTDIR_FILEID (0)

struct ffs_entry
{
    uint32_t type;
    uint32_t fileid;
    char filename[FILENAME_LEN];
};
typedef struct ffs_entry ffs_entry_t;

#ifdef __cplusplus
}
#endif
#endif
