#include "headers.h"
#include "main.h"
#include "utils.h"
#include "colours.h"
#include "Commands/process.h"
#include "Commands/history.h"
#include "Features/signals.h"
#include "Features/prompt.h"

char home[10000];
char *stream;
pid_t shellPID;

char *getInput()
{
    size_t lineReadSize = 1000;
    char *lineRead = malloc(sizeof(char) * lineReadSize);
    stream = fgets(lineRead, lineReadSize, stdin);
    lineRead[strcspn(lineRead, "\n")] = 0; // remove newline

    return lineRead;
}

void tokenize(char *input)
{
    char *token;

    while (token = strtok_r(input, ";", &input))
        tokenizeCommand(token);
}

int main()
{
    printf(bold lightPurple "\n                     Welcome to" lightPink " Magnush" reset "!\n\n" noBold);
    getcwd(home, sizeof(home));
    loadHistory();

    currentID = -1;
    shellPID = getpid();

    signal(SIGTSTP, ctrlz);
    signal(SIGINT, ctrlc);
    signal(SIGCHLD, handler);

    while (1)
    {
        prompt();
        char *input = getInput();

        if (stream == NULL)
        {
            printf("\n");
            return 0;
        }

        addCommandToHistory(input);
        tokenize(input);

        free(input);
    }

    return 0;
}
