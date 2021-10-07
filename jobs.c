#include "headers.h"

Jobs newarr[50];

int compare(const void *a, const void *b)
{
    Jobs *ja = (Jobs *)a;
    Jobs *jb = (Jobs *)b;
    return strcmp(ja->jobName, jb->jobName);
}

int setFlags(int len, char **argv)
{
    if (len == 2)
    {
        if (!strcmp(argv[1], "-r"))
            return 1;

        else if (!strcmp(argv[1], "-s"))
            return 2;

        else
        {
            perror("Incorrect argument");
            return 0;
        }
    }

    else if(len == 3)
    {
        if (!strcmp(argv[1], "-r"))
        {
            if (!strcmp(argv[2], "-s"))
                return 3;

            else
            {
                perror("Incorrect argument");
                return 0;
            }
        }

    }

    else if (len > 3)
    {
        printf("Too many arguments\n");
        return 0;
    }
}

void job(int len, char **argv)
{
    for(int i = 0; i < jobCount; i++)
        newarr[i] = jobs[i];
    
    qsort(newarr, jobCount, sizeof(Jobs), compare);

    char message[1000];
    int flag = 3;
    
    if(len > 1)
    {
        if ((flag = setFlags(len, argv)) == 0)
            return;
    }

    for (int i = 0; i < jobCount; i++)
    {
        sprintf(message, "/proc/%d/stat", newarr[i].pid);
        FILE *f;

        f = fopen(message, "r");

        if (!f)
        {
            perror("Error");
            return;
        }

        char temp[1] = {'\0'};
        char status[1000];
        fscanf(f, "%s %s %s", temp, temp, status);

        if (status[0] == 'T')
            strcpy(status, "Stopped");

        else
            strcpy(status, "Running");

        if (flag == 3 || (flag == 1 && strcmp(status, "Running") == 0 )|| (flag == 2 && strcmp(status, "Stopped") == 0))
            printf("[%d] %s %s [%d]\n", newarr[i].num, status, newarr[i].jobName, newarr[i].pid);
    }
}