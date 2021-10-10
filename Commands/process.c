#include "../headers.h"
#include "../colours.h"
#include "process.h"

Jobs jobs[50];
int jobCount;
pid_t currentID;
char currentJob[1000];
int num = 0;

void process(int len, char **argv, int isBg)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid < 0)
        perror(red "Error: Fork Failure\n" reset);

    if(pid == 0)
    {   
        if(!isBg)
            argv[len] = NULL;
        else
            setpgid(0, 0);

        if (execvp(argv[0], argv) < 0)
            printf(red "Command not found" reset ": " bold "%s\n" noBold, argv[0]);

        return;
    }
    
    else
    {
        if (!isBg)
        {
            currentID = pid;
            strcpy(currentJob, argv[0]);

            for (int i = 1; i < len; i++)
            {
                strcat(currentJob, " ");
                strcat(currentJob, argv[i]);
            }

            int status;
            wpid = waitpid(pid, &status, WUNTRACED);
        }

        else
        {

            strcpy(jobs[jobCount].jobName, argv[0]);

            for (int i = 1; i < len - 1; i++)
            {
                strcat(jobs[jobCount].jobName, " ");
                strcat(jobs[jobCount].jobName, argv[i]);
            }

            jobs[jobCount].num = ++num;
            jobs[jobCount].pid = pid;
            jobCount++;

            printf("[%d] %d %s\n", num, pid, argv[0]);
        }
    }

    return;
}
