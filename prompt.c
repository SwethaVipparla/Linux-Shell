#include "headers.h"
#include "colours.h"

void prompt() 
{
    getlogin_r(username, sizeof(username));
    gethostname(systemName, sizeof(systemName));

    sprintf(displayPrompt, "<" orange "%s" reset "@" orange"%s" reset ":", username, systemName);

    if (getcwd(cwd, sizeof(cwd)) == NULL)
       perror(red "getcwd() error" reset);

    else
    {
        if (strcmp(cwd, home) == 0)
            printf("%s" purple "~" reset "> ", displayPrompt);

        else if(strstr(cwd, home))
            printf("%s" purple "~%s" reset "> ", displayPrompt, cwd + strlen(home));
        
        else
            printf("%s" purple "%s" reset "> ", displayPrompt, cwd);
    }
}
