#ifndef CD_H
#define CD_H

extern char previousDirectory[10000], currentDirectory[10000];

void cd(int len, char **argv);

#endif