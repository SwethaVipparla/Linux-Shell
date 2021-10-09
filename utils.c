#include "headers.h"
#include "commands.h"
#include "colours.h"
#include "utils.h"
#include "Features/redirection.h"
#include "Features/pipe.h"

void tokenizeCommand(char *token)
{
    char *argv[1000], *p;
    int flag = 0;
    int stdoutSaved = dup(STDOUT_FILENO), stdinSaved = dup(STDIN_FILENO);

    if (checkPipe(token))
    {
        piping(token, stdoutSaved, stdinSaved);
        return;
    }

    if (checkRedirection(token))
        flag = 1;

    p = strtok_r(token, " \t\r", &token);
    argv[0] = p;

    int len = 1;

    while ((p = strtok_r(NULL, " \t\r", &token)) != NULL)
    {
        argv[len] = p;
        len++;
    }

    if (flag)
        len = redirectIO(len, argv);

    if (len)
        commands(len, argv);
    else
        return;

    fileStream(stdoutSaved, STDOUT_FILENO);
    fileStream(stdinSaved, STDIN_FILENO);
}

int strToInt(char *str)
{
    int num = 0;
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        int converted = str[i] - '0';

        if (converted < 0 || converted > 9)
            return 0;

        num = (num * 10) + converted;
    }

    if (num < 0)
        return 0;

    return num;
}

int fileStream(int fd, int stream)
{
    if (fd < 0)
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