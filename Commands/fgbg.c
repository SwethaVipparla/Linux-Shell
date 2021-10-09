#include "../headers.h"
#include "../colours.h"
#include "../utils.h"
#include "process.h"
#include "fgbg.h"

void fgbg(int len, char **argv, int isFg)
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

            int pid = jobs[i].pid;

            if (isFg)
            {
                strcpy(currentJob, jobs[i].jobName);
                currentID = pid;

                for (int j = i; j < jobCount - 1; j++)
                {
                    strcpy(jobs[i].jobName, jobs[i + 1].jobName);
                    jobs[i].pid = jobs[i + 1].pid;
                    jobs[i].num = jobs[i + 1].num;
                }

                jobCount--;
            }

            if (kill(pid, SIGCONT) == -1)
            {
                printf(red "fg: Error in sending SIGCONT\n" reset);
                return;
            }

            if (isFg)
            {
                int status;
                waitpid(pid, &status, WUNTRACED);
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