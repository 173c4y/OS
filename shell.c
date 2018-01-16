#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

#define BUFFERSIZE 1024

int main(int argc, char *argv[], char **envp)
{
    //clrscr();
    while(1)
    {
        char inputBuffer[BUFFERSIZE];
        char *tokens[100];
        int count = 0;
        wchar_t *s2 = (wchar_t *) calloc(20, sizeof(wchar_t));
        strcpy(s2, (wchar_t *) "\u25B6");
        printf("%sshell%s %s %s", KGRN, KBLU, s2, KNRM); //u25b6
        fgets(inputBuffer, BUFFERSIZE, stdin);
        FILE *fptr; 
        fptr = fopen(".history", "a");
        if(fptr == NULL)
        {
            printf("Permissions denied\n");
            fclose(fptr);
            continue;
        }
        else
        {
            fprintf(fptr, "%s", inputBuffer);
            fclose(fptr);
        }
        inputBuffer[strcspn(inputBuffer, "\r\n")] = 0;
        char *token;
        token = strtok(inputBuffer, " ");
        tokens[count] = token;
        while(token !=NULL)
        {
            token = strtok(NULL, " ");
            tokens[++count] = token;
        }

        // printf("\nTo print all the tokesn\n");
        // for(int i=0; i<count; i++)
        // {
        //     printf("%s\n", tokens[i]);
        // }
        if(strcmp(tokens[0], "exit") == 0)
        {
            exit(0);
        }
        if(strcmp(tokens[0], "pwd") == 0)
        {
            char buf[1024];
            getcwd(buf, 1024);
            printf("%s \n",buf);
            continue;
        }
        if(strcmp(tokens[0], "clear")==0)
        {
            system("clear");
            continue;
        }
        if(strcmp(tokens[0], "history") == 0)
        {
            int historyIndex = 0;
            if (tokens[1] == NULL)
            {
                char output[1024];
                fptr = fopen(".history", "r");
                while (!feof(fptr))
                {
                    if (fgets(output, 1024, fptr))
                    {
                        historyIndex++;
                        printf("  %d  %s", historyIndex, output);
                    }
                }
                fclose(fptr);
                continue;
            }
            if (strcmp(tokens[1], "-c") == 0)
            {
                fptr = fopen(".history", "w");
                fclose(fptr);
                continue;
            }
            int flag = 1;
            if(isdigit(tokens[1][0]) == 0)
                flag = 0;
            for (int i=0; i<strlen(tokens[1])-1; i++)
            {
                if (isdigit(tokens[1][i]) == 0)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                //printf("history number\n");
                char output[1024];
                fptr = fopen(".history", "r");
                while (!feof(fptr))
                {
                    if (fgets(output, 1024, fptr))
                    {
                        historyIndex++;
                        //printf("  %d  %s", historyIndex, output);
                    }
                }
                fclose(fptr);
                int numberOfLine = atoi(tokens[1]);
                int historyCounter = 0;
                fptr = fopen(".history", "r");
                while (!feof(fptr))
                {
                    if (fgets(output, 1024, fptr))
                    {
                        historyCounter++;
                        if (historyCounter > (historyIndex - numberOfLine))
                        {
                            printf("  %d  %s", historyCounter, output);
                        }
                    }
                }
                fclose(fptr);
            }
            else
            {
                printf("%sInvalid Usage of command.\nThe correct usage: is history [options]%s\n", KRED, KNRM);
            }
            continue;
        }
        
        // else
        // {
        //     printf("%sInvalid Usage of command.\nThe correct usage: is history [options]%s\n", KRED, KNRM);
        // }

    }
    return 0;
}