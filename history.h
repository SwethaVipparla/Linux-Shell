#ifndef HISTORY_H
#define HISTORY_H

extern int historyEntryCount;
extern char entries[20][1000];

void history(int argc, char **argv);
void addCommandToHistory(char *command);
void loadHistory();
void writeToHistory();

#endif