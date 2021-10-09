#include "../headers.h"
#include "../colours.h"
#include "../utils.h"
#include "../main.h"
#include "pinfo.h"

void pinfo(int len, char **argv)
{
    pid_t pid;

    if (len == 1)
        pid = getpid();

    else if (len == 2)
        pid = strToInt(argv[1]);

    else
    {
        printf(red "pinfo: Too many arguments\n" reset);
        return;
    }

    char exe[10000];
    char status[1000];

    sprintf(status, "/proc/%d/stat", pid);
    sprintf(exe, "/proc/%d/exe", pid);

    FILE *fp = fopen(status, "r");

    if (!fp)
    {
        printf(red "Process with pid" reset bold " %d " noBold red "does not exist\n" reset, pid);
        return;
    }

    char temp[100];
    char flag1[1000], flag2[1000];

    fscanf(fp, "%s %s %s %s %s %s %s %s", flag1, temp, status, temp, temp, temp, temp, flag2);

    int fgFlag = strcmp(flag1, flag2);
    char mpath[1000];

    sprintf(mpath, "/proc/%d/statm", pid);
    fp = fopen(mpath, "r");

    if (!fp)
    {
        printf(red "Process with pid" reset bold " %d " noBold red "does not exist\n" reset, pid);
        return;
    }

    char memory[1000];
    fscanf(fp, "%s", memory);

    char exePath[10000], *path;

    printf("pid -- %d\nProcess Status -- %s%s\nmemory -- %s {Virtual Memory}\nExecutable Path -- ", pid, status, fgFlag ? "" : "+", memory);

    int val = readlink(exe, exePath, 1000);

    if (val == -1)
        printf("NULL\n");

    else
    {
        exePath[val] = '\0';
        path = strstr(exePath, home);

        if (!path)
            printf("~%s\n", exePath);

        else
            printf("~%s\n", path + strlen(home));
    }
}