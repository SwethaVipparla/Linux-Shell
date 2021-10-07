#include "headers.h"
#include "colours.h"

void fg(int len, char **argv)
{
    if (len != 2)
    {
        printf(red "fg: Incorrect number of arguments\n" reset);
        return;
    }

    int pid, status;

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

            for (int j = i; j < jobCount - 1; j++)
            {
                strcpy(jobs[i].jobName, jobs[i + 1].jobName);
                jobs[i].pid = jobs[i + 1].pid;
                jobs[i].num = jobs[i + 1].num;
            }

            jobCount--;

            if (kill(pid, SIGCONT) == -1)
            {
                printf(red "fg: Error in sending SIGCONT\n" reset);
                return;
            }

            int status;
            while (waitpid(pid, &status, WNOHANG) != pid);

            break;
        }
    }

    if (!flag)
    {
        printf(red "sig: No such job\n" reset);
        return;
    }
}