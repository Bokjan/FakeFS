#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <cjson/cJSON.h>

int need_confirm = 1;
const char *root_path = NULL;


void parse_args(int argc, char *argv[])
{
    for(int i = 0; i < argc; ++i)
    {
        char *item = argv[i];
        if(item[0] == '-')
        {
            switch(item[1])
            {
            case 'y':
                need_confirm = 0;
                break;
            case 'd':
                root_path = argv[i + 1];
                break;
            default:
                fprintf(stderr, "Invalid argument: -%c\n", item[1]);
            }
        }
    }
}

int check_dir_available(void)
{
    if(root_path == NULL)
        return -1;
    DIR *dir = opendir(root_path);
    if(dir == NULL)
        return -1;
    closedir(dir);
    return 0;
}

int user_confirm(void)
{
    if(!need_confirm)
        return 0;
    int ret = 0;
    char input[16] = {'\0'};
    struct dirent *entry;
    DIR *dir = opendir(root_path);
    int count = 0;
    while((entry = readdir(dir)) != NULL)
        ++count;
    if(count == 2) // Only . and ..
        goto END;
    printf("Directory %s is not empty!\nContinue? [y/N] ", root_path);
    scanf("%s", input);
    if(input[0] != 'y')
        ret = -1;
END:
    closedir(dir);
    return ret;
}

void generate_config_json(void)
{
    FILE *fp = fopen("./fakefs.json", "w");
    cJSON *conf = cJSON_CreateObject();
    cJSON_AddItemToObject(conf, "root", cJSON_CreateString(root_path));
    fprintf(fp, "%s", cJSON_Print(conf));
    cJSON_Delete(conf);
    fclose(fp);
}

void generate_files(void)
{
    
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "Error: arguments too few\n");
        goto END;
    }
    parse_args(argc, argv);
    if(check_dir_available() != 0)
    {
        fprintf(stderr, "Error: path specified not available\n");
        goto END;
    }
    if(user_confirm() != 0)
    {
        fprintf(stderr, "Aborted!\n");
        goto END;
    }
    generate_files();
    generate_config_json();
END:;
}