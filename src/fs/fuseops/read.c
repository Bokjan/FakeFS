#include "../ffs.h"
#include "../def.h"
#include "../util.h"
#include <string.h>
#include <unistd.h>

int ffs_read(const char *path, char *buf, 
    size_t count, off_t offset, struct fuse_file_info *fi)
{
    int ret;
    int fd = ffs_actually_open(path, fi);
    lseek(fd, offset, SEEK_SET);
    ret = read(fd, buf, count);
    close(fd);
    return ret;
}