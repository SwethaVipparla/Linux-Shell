#include "headers.h"
#include "history.h"
#include "main.h"
#include "utils.h"
#include "colours.h"

char entries[20][1000];
char historyFile[2000];
int historyEntryCount = 0;

void addCommandToHistory(char *command)
{
    strcpy(entries[historyEntryCount % 20], command);
    historyEntryCount++;
}

void writeToHistory()
{
    FILE *fp = fopen(historyFile, "w");

    int limit = historyEntryCount < 20 ? historyEntryCount : 20;

    fprintf(fp, "%d\n", historyEntryCount);

    int i = 0;

    while(i < limit)
        fprintf(fp, "%s\n", entries[i++]);

    fclose(fp);
}

void loadHistory()
{
    strcpy(historyFile, home);
    strcat(historyFile, "/history.txt");
    FILE *fp = fopen(historyFile, "r");

    if (fp)
    {
        char line[1000] = "";
        int end = 0;

        while (fgets(line, sizeof(line), fp))
        {
            line[strcspn(line, "\n")] = 0;

            if(end)
            {
                strcpy(entries[end - 1], line);
                end++;
            }

            else 
            {
                historyEntryCount = strToInt(line);
                end = 1;
            }
        }

        fclose(fp);
    }

    else
        perror(red "history.txt" reset);

    return;
}

void history(int len, char **argv)
{
    if (len > 2)
    {
        printf(red "history: Too many arguments\n" reset);
        return;
    }

    int num = 10;
    if (len == 2)
        num = strToInt(argv[1]) > 20 ? 20 : strToInt(argv[1]);

    for (int i = historyEntryCount - num; num > 0; i++, num--)
        printf("%s\n", entries[i % 20]);
}
