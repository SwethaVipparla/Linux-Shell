#include "headers.h"

void tokenizeCommand(char *token)
{
    char *argv[1000], *p;
    int flag = 0;

    if(checkRedirection(token))
        flag = 1;

    p = strtok_r(token, " \t\r", &token);
    argv[0] = p;

    int len = 1;

    while ((p = strtok_r(NULL, " \t\r", &token)) != NULL)
    {
        argv[len] = p;
        len++;
    }

    int stdoutSaved = dup(STDOUT_FILENO), stdinSaved = dup(STDIN_FILENO);

    if(flag)
        len = redirectIO(len, argv);

    if(len)
        commands(len, argv);
    else
        return;

    dup2(stdoutSaved, STDOUT_FILENO);
    dup2(stdinSaved, STDIN_FILENO);
}

void commands(int len, char **argv)
{
    if (strcmp(argv[0], "cd") == 0)
        cd(len, argv);

    else if (strcmp(argv[0], "pwd") == 0)
        pwd();

    else if (strcmp(argv[0], "echo") == 0)
        echo(len, argv);

    else if (strcmp(argv[0], "ls") == 0)
        ls(len, argv);

    else if (strcmp(argv[0], "repeat") == 0)
        repeat(len, argv);

    else if (strcmp(argv[0], "pinfo") == 0)
        pinfo(len, argv);

    else if (strcmp(argv[0], "history") == 0)
        history(len, argv);

    else if (strcmp(argv[len - 1], "&") == 0 || argv[len - 1][strlen(argv[len - 1]) - 1] == '&')
        bg(len, argv);

    else if (strcmp(argv[0], "exit") == 0)
        exit(0);

    else
        fg(argv);

    writeToHistory();
}   