#include "headers.h"
#include "colours.h"

void pwd()
{
    char pwd[100000];
    if (getcwd(pwd, sizeof(pwd)) == NULL)
       perror(red "getcwd() error" reset);

    else    
        printf("%s\n", pwd);    
}