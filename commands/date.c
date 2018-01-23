//date
//date -R
//date -u
#include <stdio.h>
#include <time.h>
#include <string.h>
int main(int argc, char *argv[])
{
    //printf("date\n argc%d", argc);
    char timeBuffer[1024];
    time_t t = time(NULL);
    if (argc == 1)
    {
        struct tm *tm = localtime(&t);
        strftime(timeBuffer, 1024, "%a %b %d %X %Z %Y", tm); // date
        printf("%s\n", timeBuffer);
    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        struct tm *tm = gmtime(&t);
        strftime(timeBuffer, 1024, "%a %b %d %H:%M:%S UTC %Y", tm); // date -u
        printf("%s\n", timeBuffer);
    }
    else if (strcmp(argv[1], "-R") == 0)
    {
        struct tm *tm = localtime(&t);
        strftime(timeBuffer, 1024, "%a, %d %b %Y %X %z", tm); // date -R
        printf("%s\n", timeBuffer);
    }
    else
        printf("Invalid arguments");
    return 0;
}