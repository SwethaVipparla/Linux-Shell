#include "../headers.h"
#include "../colours.h"
#include "../utils.h"
#include "baywatch.h"

char *readLine(char *path, int n)
{
    FILE *file = fopen(path, "r");

    if (!file)
    {
        printf(red "baywatch: Can't open file\n" reset);
        return NULL;
    }

    char line[500];
    char *content = malloc(sizeof(char) * 500);

    for (int i = 1; fgets(line, sizeof(line), file); i++)
    {
        if (i == n)
        {
            strcpy(content, line);
            break;
        }
    }

    fclose(file);
    return content;
}

void baywatch(int len, char **argv)
{
    int interval = 0;
    int flag[4] = {0};

    FILE *fp;

    char *name = malloc(sizeof(char) * 100);

    if (len != 4)
    {
        printf(red "baywatch: Incorrect number of arguments\n");
        return;
    }

    for (int i = 1; i < len; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            if (i + 1 == len)
            {
                printf(red "replay: Incorrect number of arguments\n" reset);
                return;
            }

            if (!(interval = strToInt(argv[i + 1])))
            {

                printf(red "replay: Invalid interval\n" reset);
                return;
            }

            i++;
        }

        else if (strcmp(argv[i], "interrupt") == 0)
        {
            flag[0] = 1;

            char *line = readLine("/proc/interrupts", 1);

            if (!line)
                return;

            printf("%s\n", line);
            free(line);
        }

        else if (strcmp(argv[i], "newborn") == 0)
            flag[1] = 1;

        else if (strcmp(argv[i], "dirty") == 0)
            flag[2] = 1;

        else
        {
            printf(red "baywatch: Invalid argument\n" reset);
            return;
        }
    }

    while (1)
    {
        fd_set fds;
        struct timeval tv;
        tv.tv_sec, tv.tv_usec = 0;

        FD_ZERO(&fds);
        FD_SET(0, &fds);

        int val = select(1, &fds, NULL, NULL, &tv);

        if (val)
        {
            val = select(1, &fds, NULL, NULL, &tv);

            if (fgetc(stdin) == 'q')
            {
                printf("\r");
                return;
            }
        }

        else if (val == -1)
            perror(red "select" reset);

        if (flag[0] == 1)
        {
            char *line = readLine("/proc/interrupts", 3);
            if (!line)
                return;

            for (int i = 0; i < strlen(line); i++)
            {
                if (line[i] == 'I')
                {
                    line[i] = '\0';
                    break;
                }
            }

            printf("%s\n", line);
            free(line);
        }

        else if (flag[1] == 1)
        {
            char *line = readLine("/proc/loadavg", 1);

            if (!line)
                return;

            char *token = strtok(line, " ");
            char *newborn;

            while (token != NULL)
            {
                newborn = token;
                token = strtok(NULL, " ");
            }

            printf("%s", newborn);
            free(line);
        }

        else if (flag[2] == 1)
        {
            char *line = readLine("/proc/meminfo", 17);

            if (!line)
                return;

            printf("%s\n", line);
            free(line);
        }

        sleep(interval);
    }
}