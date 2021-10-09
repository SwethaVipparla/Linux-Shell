#include "../headers.h"
#include "../colours.h"
#include "../utils.h"
#include "process.h"
#include "sig.h"

void sig(int len, char **argv)
{
    int flag = 0;
    if (len != 3)
    {
        printf(red "sig: Enter 3 arguments\n" reset);
        return;
    }
    int inputJobNumber = strToInt(argv[1]);
    int signalNumber = strToInt(argv[2]);

    if (inputJobNumber < 1)
    {
        printf(red "sig: Invalid job number\n" reset);
        return;
    }

    if (signalNumber < 1 || signalNumber > 31)
    {
        printf(red "sig: Invalid signal number\n" reset);
        return;
    }

    for (int i = 0; i < jobCount; i++)
    {
        if (jobs[i].num == inputJobNumber)
        {
            flag = 1;
            if (kill(jobs[i].pid, signalNumber) < 0)
            {
                printf(red "sig: Error while killing\n" reset);
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