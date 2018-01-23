#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Invalid Arguments\n");
    }
    else if (argc == 2)
    {
        struct stat path_stat;
        stat(argv[1], &path_stat);
        int is_file = S_ISREG(path_stat.st_mode);
        int is_dir = S_ISDIR(path_stat.st_mode);
        if (is_file)
            remove(argv[1]);
        else
            printf("Not a File\n");
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-i") == 0)
        {
            struct stat path_stat;
            stat(argv[2], &path_stat);
            int is_file = S_ISREG(path_stat.st_mode);
            int is_dir = S_ISDIR(path_stat.st_mode);
            printf("Delete file? (y/n) : ");
            char choice;
            scanf("%c", &choice);
            if (choice == 'y' && is_file)
            {
                remove(argv[2]);
            }
        }
        else if (strcmp(argv[1], "-d") == 0)
        {
            struct stat path_stat;
            stat(argv[2], &path_stat);
            int is_file = S_ISREG(path_stat.st_mode);
            int is_dir = S_ISDIR(path_stat.st_mode);
            if (is_dir)
            {
                struct dirent *d;
                DIR *dir = opendir(argv[2]);
                int count = 0;
                if (dir == NULL)
                    printf("Error reading file\n");
                else
                {
                    while ((d = readdir(dir)) != NULL)
                    {
                        count++;
                    }
                    if (count > 2)
                        printf("Directory not empty\n");
                    else
                        remove(argv[2]);
                }
                closedir(dir);
            }
            else 
                printf("Not a Directory\n%d", is_dir);
        }
        else
            printf("Invalid Arguments\n");
    }
    return 0;
}