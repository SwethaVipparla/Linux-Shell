#include "../headers.h"
#include "../colours.h"
#include "../main.h"
#include "../Commands/process.h"
#include "signals.h"
#include "prompt.h"

void ctrlz(int sig)
{
    pid_t p = getpid();

    if (p != shellPID)
        return;

    if (currentID != -1)
    {
        if (kill(currentID, SIGTSTP) == -1)
            return;

        jobs[jobCount].pid = currentID;
        strcpy(jobs[jobCount].jobName, currentJob);
        jobs[jobCount].num = ++num;
        jobCount++;
    }

    return;
}

void ctrlc(int sig)
{
    pid_t p = getpid();

    if (p != shellPID)
        return;

    if (currentID != -1)
    {
        if (kill(currentID, SIGINT) == -1)
            return;
    }

    return;
}

void handler(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0)
    {
        char message[200];
        int i = 0, flag = 0;

        while (i < jobCount)
        {
            if (jobs[i].pid == pid)
            {
                sprintf(message, bold "\n%s" noBold, jobs[i].jobName);
                for (int j = i; j < jobCount - 1; j++)
                {
                    jobs[j].pid = jobs[j + 1].pid;
                    strcpy(jobs[j].jobName, jobs[j + 1].jobName);
                    jobs[j].num = jobs[j + 1].num;
                }
                flag = 1;
                jobCount--;
                break;
            }

            i++;
        }

        if (WIFEXITED(status) && !WEXITSTATUS(status) && flag)
            fprintf(stderr, bold "%s " noBold green "with pid " reset bold "%d " noBold green "exited normally\n" reset, message, pid);

        else
            fprintf(stderr, bold "%s " noBold red "with pid " reset bold "%d " noBold red "exited abnormally\n" reset, message, pid);

        prompt();

        fflush(stderr);
        fflush(stdout);
    }

    return;
}