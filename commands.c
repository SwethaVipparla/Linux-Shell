#include "headers.h"
#include "commands.h"
#include "Commands/cd.h"
#include "Commands/pwd.h"
#include "Commands/echo.h"
#include "Commands/ls.h"
#include "Commands/repeat.h"
#include "Commands/pinfo.h"
#include "Commands/history.h"
#include "Commands/process.h"
#include "Commands/jobs.h"
#include "Commands/sig.h"
#include "Commands/fgbg.h"
#include "Commands/replay.h"
#include "Commands/baywatch.h"
#include "utils.h"

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
    {
        if (strcmp(argv[len - 1], "&") == 0)
            argv[len - 1] = NULL;

        else if (argv[len - 1][strlen(argv[len - 1]) - 1] == '&')
            argv[len - 1][strlen(argv[len - 1]) - 1] = '\0';

        process(len, argv, 1);
    }

    else if (strcmp(argv[0], "jobs") == 0)
        job(len, argv);

    else if (strcmp(argv[0], "sig") == 0)
        sig(len, argv);

    else if (strcmp(argv[0], "fg") == 0)
        fgbg(len, argv, 1);

    else if (strcmp(argv[0], "bg") == 0)
        fgbg(len, argv, 0);

    else if (strcmp(argv[0], "replay") == 0)
        replay(len, argv);

    else if (strcmp(argv[0], "baywatch") == 0)
        baywatch(len, argv);

    else if (strcmp(argv[0], "exit") == 0)
        exit(0);

    else
        process(len, argv, 0);

    writeToHistory();
}