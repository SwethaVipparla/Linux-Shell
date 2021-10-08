#include "headers.h"
#include "colours.h"

void ctrlz(int sig) 
{
    pid_t p = getpid();

    if(p != shellPID)
        return;

    if (currentID != -1)
    {
        if(kill(currentID, SIGTSTP) == -1)
            perror(red "kill" reset);

        jobs[jobCount].pid = currentID;
        strcpy(jobs[jobCount].jobName, currentJob);
        jobs[jobCount].num = ++num;
        jobCount++; 
        return;
    }

    return;
} 

void ctrlc(int sig) 
{
    pid_t p = getpid();

    if(p != shellPID)
        return;

    if (currentID != -1)
    {
        if(kill(currentID, SIGINT) == -1)
            perror(red "kill" reset);
    }
    
    signal(SIGINT, ctrlc);
    return;
}