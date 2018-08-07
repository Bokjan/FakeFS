#include <map>
#include <string>
#include "util.h"

using std::string;

static std::map<string, int> fdmap;

int  ffs_fdmap_get(const char *path)
{
    auto f = fdmap.find(path);
    return f == fdmap.end() ? -1 : f->second;
}

void ffs_fdmap_set(const char *path, int fd)
{
    fdmap[path] = fd;
}

void ffs_fdmap_remove(const char *path)
{
    auto f = fdmap.find(path);
    if(f != fdmap.end())
        fdmap.erase(f);
}