#include "ffs.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

int ffs_init(const char *conf)
{
    if(conf == NULL)
        conf = "./fakefs.json";
    FILE *f = fopen(conf, "r");
    if(f == NULL)
        return -1;
    int conf_size = ffsi_get_file_size(f);
    void *mem = malloc(conf_size + 16);
    if(mem == NULL)
        return -1;
    fread(mem, conf_size, 1, f);
    cJSON *obj = cJSON_Parse(mem);
    if(obj == NULL)
    {
        const char *err = cJSON_GetErrorPtr();
        if(err != NULL)
            fprintf(stderr, "Config error: %s\n", err);
        return -1;
    }
    const cJSON *root_path = cJSON_GetObjectItemCaseSensitive(obj, "root");
    if(cJSON_IsString(root_path) && root_path->valuestring != NULL)
    {
        int len = strlen(root_path->valuestring);
        ffs_root = (char*)malloc(len + 2);
        ffs_root[len + 1] = '\0';
        strcpy(ffs_root, root_path->valuestring);
        if(ffs_root[len - 1] != '/')
            ffs_root[len] = '/';
        ffs_root_len = strlen(ffs_root);
    }
    else
        return -1;
    /*
        When -1 returning, FakeFS won't work.
        So `free(mem)` only appears here.
    */
    free(mem);
    return 0;
}