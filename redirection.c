#include "headers.h"

int checkRedirection(char *token)
{
    char *input, *output, *append;

    input = strstr(token, "<");
    output = strstr(token, ">");
    append = strstr(token, ">>");

    if (input != NULL || output != NULL || append != NULL)
        return 1;
    else 
        return 0;
}

int fileStream(int fd, int stream)
{
    if(fd < 0)
    {
        printf("Error: File not found\n");
        return 0;
    }
    if (dup2(fd, stream) < 0)
    {
        printf("Error: Cannot redirect\n");
        return 0;
    }
    close(fd);
}

int redirectIO(int len, char **argv)
{
    int newLen = 0;

    for(int i = 0; i < len; i++)
    {
        if (strcmp(argv[i], "<") == 0 && i + 1 < len)
        {
            int fd = open(argv[i++ + 1], O_RDONLY, 0644);
            fileStream(fd, STDIN_FILENO);
            continue;
        }

        else if (strcmp(argv[i], ">") == 0 && i + 1 < len)
        {
            int fd = open(argv[i++ + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            fileStream(fd, STDOUT_FILENO);
            continue;
        }

        else if(strcmp(argv[i], ">>") == 0 && i + 1 < len)
        {
            int fd = open(argv[i++ + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            fileStream(fd, STDOUT_FILENO);
            continue;
        }

        else 
        {
            strcpy(argv[newLen], argv[i]);
            newLen++;
            continue;
        }

        return 0;
    }

    for(int i = newLen; i < len; i++)
        argv[i] = NULL;

    return newLen;
}