#include "../headers.h"
#include "../commands.h"
#include "../colours.h"
#include "../utils.h"
#include "repeat.h"

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
