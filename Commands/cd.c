#include "../headers.h"
#include "../colours.h"
#include "../main.h"
#include "cd.h"

char previousDirectory[10000], currentDirectory[10000];

void cd(int len, char **argv)
{
    getcwd(currentDirectory, sizeof(currentDirectory));

    if (len > 2)
        printf(red "cd error: Too many arguments\n" reset);

    else if (len == 1 || strcmp(argv[1], "~") == 0)
        chdir(home);

    else if (strcmp(argv[1], "-") == 0)
    {
        printf("%s\n", previousDirectory);
        chdir(previousDirectory);
    }

    else if (chdir(argv[1]))
        printf(red "cd error: No such file or directory\n" reset);

    strcpy(previousDirectory, currentDirectory);
}