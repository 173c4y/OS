#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buffer[1024];
    FILE *fptr;
    // printf("argc: %d\n", argc);
    if (argc == 1)
    {
        printf("Invalid Arguments\n");
    }
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
        {
            printf("Invalid Arguments\n");
            return 0;
        }
        fptr = fopen(argv[1], "r");
        while (!feof(fptr))
                {
                    if (fgets(buffer, 1024, fptr))
                    {
                        //historyIndex++;
                        printf("%s", buffer);
                    }
                }
                fclose(fptr);
                printf("\n");
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-u") == 0)
        {
            // printf(" - u \n");
            int count = 1;
            fptr = fopen(argv[2], "r");
            while (!feof(fptr))
                {
                    if (fgets(buffer, 1024, fptr))
                    {
                        //historyIndex++;
                        printf("%d    %s", count, buffer);
                        count++;
                    }
                }
                fclose(fptr);
                printf("\n");
        }
        else if (strcmp(argv[1], "-E") == 0)
        {
            fptr = fopen(argv[2], "r");
            while (!feof(fptr))
                {
                    if (fgets(buffer, 1024, fptr))
                    {
                        //historyIndex++;
                        char *p;
                        p = strtok(buffer, "\n");
                        if(p == NULL)
                            printf("$\n");
                        else
                            printf("%s$\n", p);
                    }
                }
                fclose(fptr);
                printf("\n");
        }
        else
            printf("Invalid Arguments\n");
        // printf("%s\n%s", argv[1], argv[2]);
    }
    else
        printf("Invalid Arguments\n");
    return 0;
}