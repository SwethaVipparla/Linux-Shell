#include "headers.h"
#include "colours.h"

char* getInput()
{
    size_t lineReadSize = 1000;
    char *lineRead = malloc(sizeof(char) *lineReadSize);
    getline(&lineRead, &lineReadSize, stdin);
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
    printf(bold lightPurple "\n                     Welcome to" lightPink " Magnush!\n\n" reset noBold);
    getcwd(home, sizeof(home));
    loadHistory();

    while (1)
    {
        prompt();
        char *input = getInput();

        addCommandToHistory(input);
        tokenize(input);
    }

    return 0;
}
