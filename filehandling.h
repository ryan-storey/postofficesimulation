#ifndef __FILEHANDLING_H
#define __FILEHANDLING_H
#include <stdio.h>
#include <parameters.h>
#include <errno.h>
extern void printState(FILE *, int, int, int, int, int, int);
extern void printAverages(FILE *, int, int, int, float,int, int);
extern FILE *openFile(char *);
extern void printParameters(char *, PARAMETERS *);

#endif
