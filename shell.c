#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wchar.h>
#include <locale.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[93m"
#define KBLU  "\x1B[34m"

#define BUFFERSIZE 1024
int main(int argc, char *argv[], char **envp)
{
    system("clear");
    setlocale(LC_ALL, "");
    char defaultFolder[BUFFERSIZE];
    getcwd(defaultFolder, BUFFERSIZE);
    char commandsFolder[BUFFERSIZE];
    strcpy(commandsFolder, defaultFolder);
    strcat(commandsFolder, "/commands/");
    strcat(defaultFolder, "/.history");
    while(1)
    {
        char tmpCommandsFolder[BUFFERSIZE];
        char inputBuffer[BUFFERSIZE];
        char *tokens[100];
        int count = 0;
        char curDir[BUFFERSIZE];
        char oldDir[BUFFERSIZE];
		getcwd(curDir, BUFFERSIZE);
        if (getuid() == 0)
            printf("%sshell%s %lc %s ", KGRN, KBLU, (wint_t)9813, KNRM); //queen
        else
            printf("%sshell%s %lc %s ", KGRN, KBLU, (wint_t)9812, KNRM); //king
        fgets(inputBuffer, BUFFERSIZE, stdin);
        FILE *fptr; 
        fptr = fopen(defaultFolder, "a");
        if(fptr == NULL)
        {
            printf("WHATEVER\n");
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
        while(token != NULL)
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
            if (tokens[1] != NULL)
            {
                printf("%sInvalid Usage of command.\nThe correct usage: is pwd%s\n", KRED, KNRM);
                continue;
            }
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
                fptr = fopen(defaultFolder, "r");
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
                fptr = fopen(defaultFolder, "w");
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
                fptr = fopen(defaultFolder, "r");
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
                fptr = fopen(defaultFolder, "r");
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
        if (strcmp(tokens[0], "echo") == 0)
        {
            //printf("noob shit going in here");
            if (tokens[2] == NULL)
            {
                int length = strlen(tokens[1]);
                //printf("%d\n", length);
                for (int i = 0; i < length; i++)
                {
                    if (tokens[1][i] == '"')
                        continue;

                    printf("%c", tokens[1][i]);
                }
                printf("\n");
                continue;
            }
            if(strcmp(tokens[1], "-n") == 0)
            {
                int length = strlen(tokens[2]);
                for (int i = 0; i < length; i++)
                {
                    if(tokens[1][i] == '"')
                        continue;
                    printf("%c", tokens[2][i]);
                }
                continue;
            }
            if (strcmp(tokens[1], "-E") == 0)
            {
                int length = strlen(tokens[2]);
                for (int i = 0; i < length; i++)
                {
                    if (tokens[1][i] == '"')
                        continue;
                    printf("%c", tokens[2][i]);
                }
                printf("\n");
                continue;
           }
           printf("%sInvalid Usage of command.\nThe correct usage: is echo [options] [string]%s\n", KRED, KNRM);
        }
        if (strcmp(tokens[0], "cd") == 0)
        {  
            if (tokens[1] != NULL){
				if (strcmp(tokens[1], "~") == 0)
                {
					//char * homeDir = getenv("HOME");
					chdir(getenv("HOME"));
					setenv("OLDPWD", curDir, 1);
				} else if (strcmp(tokens[1], "-") == 0)
                {
					char * oldPWD = getenv("OLDPWD");
					chdir(oldPWD);
					setenv("OLDPWD", curDir, 1);
				} else 
                {
					if (chdir(tokens[1]) != 0)
                    {
						printf("cd: no such file or directory: %s\n", tokens[1]);	
					}
				}
			} else 
            {
				if (chdir(getenv("HOME")) != 0)
                {
					printf("Cannot process\n");	
				} else 
					setenv("OLDPWD", curDir, 1);
			}
            continue;
        }
        int lsCheck = strcmp(tokens[0], "ls");
        int dateCheck = strcmp(tokens[0], "date");
        int rmCheck = strcmp(tokens[0], "rm");
        int mkdirCheck = strcmp(tokens[0], "mkdir");
        int catCheck = strcmp(tokens[0], "cat");
        if (!lsCheck || !dateCheck || !rmCheck || !mkdirCheck || !catCheck)
        {
            strcpy(tmpCommandsFolder, commandsFolder);
            //printf("this is the original tmp folder %s %s \n", tmpCommandsFolder, tokens[0]);
            strcat(tmpCommandsFolder, tokens[0]);
            if (fork() == 0)
            {
                //printf("\ngoing into child with %s\n", tmpCommandsFolder);
                execvp(tmpCommandsFolder, tokens);
            }
            else
            {
                //printf("\ngoing into parent\n");
                wait(NULL);
            }
            continue;
        }
        printf("%sInvalid command%s\n", KRED, KNRM);
        // if (strcmp(tokens[0], "") == 0)
        // {
        //     continue;
        // }
        // else
        // {
        //     printf("%sInvalid Usage of command.\nThe correct usage: is history [options]%s\n", KRED, KNRM);
        // }

    }
    return 0;
}