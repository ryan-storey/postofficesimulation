#ifndef __STACK_H
#define __STACK_H
#define TRUE 1 
#define FALSE 0

#include <stdlib.h>
#include <stdio.h>

struct anode
{
   int           taskTime;
   int           maxWaitingTime;
   unsigned int   waitingTime;
   struct anode  *nextCustomer;
   struct anode  *prevCustomer;
};

struct queueStruct
{
   struct anode *rear;
   struct anode *front;
   int          size;
   int          maxSize;
};

typedef struct queueStruct QUEUE;
typedef struct anode NODE;
typedef char BOOLEAN;

extern BOOLEAN isQueueEmpty(QUEUE *);
extern BOOLEAN isQueueFull(QUEUE *);
extern int  dequeue    (int, QUEUE **);
extern void  enqueue   (QUEUE **, NODE *);
extern QUEUE* createQueue(int maxSize);
extern void  freeList      (QUEUE **);
extern NODE *newNode       (int);
#endif
