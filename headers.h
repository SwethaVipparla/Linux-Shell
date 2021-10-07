#ifndef HEADERS_H
#define HEADERS_H

/*------Headers------*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <grp.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

/*------Variable Declarations------*/

// main.c
extern char home[10000];

// prompt.c
extern char username[10000], systemName[10000], cwd[10000], displayPrompt[40000];

// cd.c
extern char previousDirectory[10000], currentDirectory[10000];

// bg.c
typedef struct jobs 
{
    char jobName[100];
    pid_t pid;
} Jobs;

extern Jobs jobs[50];

// history.c
extern int historyEntryCount;
extern char entries[20][1000];

/*------Function Definitions-----*/

// prompt.c
void prompt();

// commands.c
void tokenizeCommand(char *token);
void commands(int len, char **argv);

// cd.c
void cd(int len, char **argv);

// pwd.c
void pwd();

// echo.c
void echo(int len, char **argv);

// ls.c
void ls(int argc, char **argv);

// fg.c
void fg(char **token);

// bg.c
void bg(int len, char **argv);

// pinfo.c
void pinfo(int argc, char **argv);

// repeat.c
int strToInt(char *str);
void repeat(int len, char **argv);

// history.c
void history(int argc, char **argv);
void addCommandToHistory(char *command);
void loadHistory();
void writeToHistory();

// redirection.c
int checkRedirection(char *token);
int redirectIO(int len, char **argv);
int fileStream(int fd, int stream);

// pipe.c
int checkPipe(char *token);
void piping(char *token, int stdoutSaved, int stdinSaved);

#endif
