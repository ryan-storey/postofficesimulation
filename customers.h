#ifndef __CUSTOMERS_H
#define __CUSTOMERS_H
#include <parameters.h>
#include <linkedlist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

extern void increaseWaitingTimes(QUEUE **, int *);
extern void  newCustomersArrive(QUEUE **, int *,gsl_rng *,PARAMETERS *);
extern void  serveCustomers (int **, QUEUE **, int, int *, int *);
#endif

