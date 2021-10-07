#include "headers.h"
#include "colours.h"

int jobCount;
Jobs jobs[50];

int num = 0;

void handler(int signum)
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

void background(int len, char **argv)
{
    if (strcmp(argv[len - 1], "&") == 0)
        argv[len - 1] = NULL;

    else if (argv[len - 1][strlen(argv[len - 1]) - 1] == '&')
        argv[len - 1][strlen(argv[len - 1]) - 1] = '\0';

    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid < 0)
        perror(red "Error: Fork Failure \n" reset);

    else if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(argv[0], argv) < 0)
            printf(red "Command not found" reset ": " bold "%s\n" noBold, argv[0]);

        exit(0);
    }

    else
    {
        signal(SIGCHLD, handler);
        strcpy(jobs[jobCount].jobName, argv[0]);
        for (int i = 1; i < len - 1; i++)
        {
            strcat(jobs[jobCount].jobName, " ");
            strcat(jobs[jobCount].jobName, argv[i]);
        }
        jobs[jobCount].num = ++num;
        jobs[jobCount].pid = pid;
        jobCount++;
        printf("[%d] %d %s\n", jobCount, pid, argv[0]);
    }

    return;
}
