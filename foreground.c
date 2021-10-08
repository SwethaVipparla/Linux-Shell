#include "headers.h"
#include "colours.h"

 pid_t currentID;
 char currentJob[1000];

void foreground(int len, char **argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid < 0)
        perror(red "Error: Fork Failure\n" reset);

    else if (pid == 0)
    {
        if (execvp(argv[0], argv) < 0)
            printf(red "Command not found" reset ": " bold "%s\n" noBold, argv[0]);
        return;
    }
    
    else
    {
        currentID = pid;
        
        strcpy(currentJob, argv[0]);
        int status;

        for (int i = 1; i < len - 1; i++)
        {
            strcat(currentJob, " ");
            strcat(currentJob, argv[i]);
        }

        wpid = waitpid(pid, &status, WUNTRACED);
    }
}

