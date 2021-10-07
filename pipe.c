#include "headers.h"

int checkPipe(char *token)
{
    char *pipe;
    pipe = strstr(token, "|");
    
    if (pipe)
        return 1;

    return 0;
}

void piping(char *token, int stdoutSaved, int stdinSaved)
{
    char *args[1000];

    char *p = strtok_r(token, "|", &token);
    int len = 0;

    while (p)
    {
        args[len++] = p;
        p = strtok_r(NULL, "|", &token);
    }

    int fd[2], i = 0;

    while(i < len - 1)
    {
        if (pipe(fd) < 0)
        {
            perror("Pipe error");
            return;
        }

        fileStream(fd[1], STDOUT_FILENO);
        tokenizeCommand(args[i++]);
        fileStream(fd[0], STDIN_FILENO);
    }

    fileStream(stdoutSaved, STDOUT_FILENO);
    tokenizeCommand(args[len - 1]);
    fileStream(stdinSaved, STDIN_FILENO);
}
