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

int redirectInput(int len, char **argv)
{
    int i = 0, newLen = 0;
    while(i++ <= len)
    {
        if (strcmp(argv[i], "<") == 0 && i + 1 <= len)
        {
            int fd = open(argv[i + 1], O_RDONLY, 0644);
            if(fd < 0)
            {
                printf("Error: File not found\n");
                return 0;
            }
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                printf("Error: Cannot redirect input\n");
                return 0;
            }
            close(fd);
        }

        else if (strcmp(argv[i], ">") == 0 && i + 1 <= len)
        {
            int fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd < 0)
            {
                printf("Error: File not found\n");
                return 0;
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                printf("Error: Cannot redirect output\n");
                return 0;
            }
            close(fd);
        }

        else if(strcmp(argv[i], ">>") == 0 && i + 1 <= len)
        {
            int fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(fd < 0)
            {
                printf("Error: File not found\n");
                return 0;
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                printf("Error: Cannot redirect output\n");
                return 0;
            }
            close(fd);
        }

        else 
        {
            strcpy(argv[newLen], argv[i]);
            newLen++;
        }
        
        i = newLen;

        while(i++ <= len)
            strcpy(argv[i], '\0');

        return (newLen - 1);
    }
}
    