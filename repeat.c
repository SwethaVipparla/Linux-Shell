#include "headers.h"
#include "colours.h"

int strToInt(char *str)
{
    int num = 0;
    int n = strlen(str);

    for (int i = 0; i < n; i++)
    {
        int converted = str[i] - '0';

        if (converted < 0 || converted > 9)
            return 0;

        num = (num * 10) + converted;
    }

    if(num < 0)
        return 0;

    return num;
}

void repeat(int len, char **argv)
{
    if (len < 3)
    {
        printf(red "Not enough arguments\n" reset);
        return;
    }

    char *ptr;
    int number = strToInt(argv[1]);

    if (!number)
    {
        printf(red "Invalid number\n" reset);
        return;
    }

    for (int i = 0; i < number; i++)
        commands(len - 2, argv + 2);
}
