//ls -a
//ls -1
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    char *files[100];
    int count = 0;
    int flag = 0;
    struct dirent *curDir;
    DIR *dirPointer = opendir(".");
    if (dirPointer == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }
    if (argc == 1)
    {
        while ((curDir = readdir(dirPointer)) != NULL)
        {   
            if (curDir->d_name[0] == '.')
                continue;
            files[count] = strdup (curDir->d_name);
            count++;
        }
        for (int i = 0; i < count-1; i++)
        {
            for (int j = i+1; j < count; j++)
            {
                if (strcasecmp(files[i], files[j]) > 0)
                {
                    char *tmp = files[i];
                    files[i] = files[j];
                    files[j] = tmp;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            printf("%s  ", files[i]);
        }
        printf("\n");
        closedir(dirPointer);
    }
    else if (strcmp(argv[1], "-a") == 0)
    {
        while ((curDir = readdir(dirPointer)) != NULL)
        {   
            files[count] = strdup (curDir->d_name);
            count++;
        }
        for (int i = 0; i < count-1; i++)
        {
            for (int j = i+1; j < count; j++)
            {
                if (strcasecmp(files[i], files[j]) > 0)
                {
                    char *tmp = files[i];
                    files[i] = files[j];
                    files[j] = tmp;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            printf("%s  ", files[i]);
        }
        printf("\n");
        closedir(dirPointer);
    }
    else if (strcmp(argv[1], "-1") == 0)
    {
        while ((curDir = readdir(dirPointer)) != NULL)
        {   
            if (curDir->d_name[0] == '.')
                continue;
            files[count] = strdup (curDir->d_name);
            count++;
        }
        for (int i = 0; i < count-1; i++)
        {
            for (int j = i+1; j < count; j++)
            {
                if (strcasecmp(files[i], files[j]) > 0)
                {
                    char *tmp = files[i];
                    files[i] = files[j];
                    files[j] = tmp;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            printf("%s\n", files[i]);
        }
        closedir(dirPointer);
    }
    else
    {
        printf("Invalid argument\n");
        closedir(dirPointer);
    }
    // if (flag !=)
    // {
    //     for (int i = 0; i < count; i++)
    //     {
    //         printf("%s  ", files[i]);
    //     }
    //     printf("\n");
    // }
    return 0;
}