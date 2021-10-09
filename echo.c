#include "headers.h"
#include "echo.h"

void echo(int len, char **argv)
{
    for(int i = 1; i < len; i++)
		printf("%s ", argv[i]);
        
	printf("\n");
}
