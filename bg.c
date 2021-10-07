#include "headers.h"
#include "colours.h"

void bg(int len, char **argv)
{
    if (len != 2)
    {
        printf(red "fg: Incorrect number of arguments\n" reset);
        return;
    }

    int inputJobNumber = strToInt(argv[1]);

    if (inputJobNumber < 1)
    {
        printf(red "sig: Invalid job number\n" reset);
        return;
    }

    int flag = 0;

    for (int i = 0; i < jobCount; i++)
    {
        if (jobs[i].num == inputJobNumber)
        {
            flag = 1;
            char *jobName = jobs[i].jobName;
            int pid = jobs[i].pid;

            if (kill(pid, SIGCONT) == -1)
            {
                printf(red "fg: Error in sending SIGCONT\n" reset);
                return;
            }

            break;
        }
    }

    if (!flag)
    {
        printf(red "sig: No such job\n" reset);
        return;
    }
}