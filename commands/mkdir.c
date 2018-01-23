#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
        printf("Invalid Command\n");
    else if (argc == 2)
    {
        if (mkdir(argv[1], 0777) !=0)
            printf("Unable to create directory\n");
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-v") == 0)
        {
            if (mkdir(argv[2], 0777) !=0)
                printf("Unable to create directory\n");
            else
                printf("Directory created\n");
        }
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-m") == 0)
        {
            char *p;
            long perm = strtoul(argv[2], &p, 8);
            if (mkdir(argv[3], perm) !=0)
                printf("Unable to create directory\n");
            else
                printf("Directory created\n");
        }
    }
    else 
        printf("Invalid arguments\n");
    return 0;
}