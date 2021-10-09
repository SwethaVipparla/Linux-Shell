#include "../headers.h"
#include "../commands.h"
#include "../colours.h"
#include "../utils.h"
#include "replay.h"

void replay(int len, char **argv)
{
    if (len < 7)
    {
        printf(red "replay: Incorrect number of arguments\n" reset);
        return;
    }

    int flag[4] = {0};
    int times[2] = {0};

    char *command[1000];
    int comLen = 0;

    for (int i = 1; i < len; i++)
    {
        if (strcmp(argv[i], "-command") == 0)
            flag[0] = 1;

        else if (strcmp(argv[i], "-interval") == 0)
        {
            flag[1] = 1;

            if (i + 1 == len)
            {
                printf(red "replay: Incorrect number of arguments\n" reset);
                return;
            }

            if (!(times[0] = strToInt(argv[i + 1])))
            {

                printf(red "replay: Invalid interval\n" reset);
                return;
            }

            i++;
        }

        else if (strcmp(argv[i], "-period") == 0)
        {
            flag[2] = 1;

            if (i + 1 == len)
            {
                printf(red "replay: Incorrect number of arguments\n" reset);
                return;
            }

            if (!(times[1] = strToInt(argv[i + 1])))
            {
                printf(red "replay: Invalid period\n" reset);
                return;
            }

            i++;
        }

        else if (flag[0])
        {
            flag[3] = 1;
            command[comLen++] = argv[i];
        }
    }

    if (!flag[1] || !flag[2] || !flag[3])
    {
        printf(red "replay: Improper arguments\n" reset);
        return;
    }

    int timesExecute = times[1] / times[0];
    for (int i = 0; i < timesExecute; i++)
    {
        char *commandCopy[1000];

        for (int j = 0; j < comLen; j++)
            commandCopy[j] = command[j];

        sleep(times[0]);
        commands(comLen, commandCopy);
    }
}
