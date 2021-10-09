#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

typedef struct jobs 
{
    int num;
    char jobName[100];
    pid_t pid;
} Jobs;

extern Jobs jobs[50];
extern pid_t currentID;
extern char currentJob[1000];
extern int jobCount, num;

void process(int len, char **argv, int isBg);

#endif