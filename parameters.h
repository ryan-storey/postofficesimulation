#ifndef __PARAMETERS_H
#define __PARAMETERS_H
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

struct parametersStruct
{
   int maxQueueLength;
   int numServicePoints;
   int closingTime;
   int meanCustomers;
   int sdNewCustomers;
   int meanPatience;
   int sdPatience;
   int meanTaskTime;
   int sdTaskTime;
};


typedef struct parametersStruct PARAMETERS;

extern PARAMETERS *readFromFile(char *);
static void checkIfValid(int);
#endif
