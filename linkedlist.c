#include <linkedlist.h>
NODE *newNode (int id)
{
   NODE *n = (NODE *)malloc(sizeof(NODE));
   if ( n==NULL )
   {
      fprintf(stderr,"Insufficient memory\n");
      exit(-3);
   }
   n->taskTime = 0;
   n->maxWaitingTime = 0;
   n->waitingTime = 0;
   n->nextCustomer = NULL;
   n->prevCustomer = NULL;

   return n;
}


BOOLEAN isQueueFull(QUEUE *q)
{
   if(q->size == q->maxSize)
      return TRUE;
   else
      return FALSE;
}

QUEUE *createQueue(int maxSize)
{
   QUEUE *q = (QUEUE *)malloc(sizeof(QUEUE));
   if ( q==NULL )
   {
      fprintf(stderr,"Insufficient memory\n");
      exit(-3);
   }
   q->maxSize = maxSize;
   q->size = 0;
   q->rear = NULL;
   q->front = NULL;

   return q;
}
BOOLEAN isQueueEmpty(QUEUE *q)
{
   if(q->rear == NULL)
   {
      return TRUE;
   }
   else
      return FALSE;
}

void enqueue (QUEUE **q, NODE *node)
{
   if (isQueueEmpty(*q)){
      (*q)->rear = node;
      (*q)->front = node;
   }
   else
   {
      ((*q)->rear)->prevCustomer = node;
      node->nextCustomer = (*q)->rear;
      (*q)->rear = node;
   }
   (*q)->size++;
}

int dequeue (int index, QUEUE **q)
{
   int i = 0;
   NODE *currentNode = (*q)->front;
   NODE *prev = NULL;
   NODE *next = NULL;
   if(isQueueEmpty(*q))
      return 0;
   while(currentNode != NULL && i != index){
      currentNode = currentNode->prevCustomer;
      i++;
   }
   prev = currentNode->prevCustomer;
   next = currentNode->nextCustomer;
   if(prev == NULL && next == NULL){
      (*q)->rear = NULL;
      (*q)->front = NULL;
   }else if(next == NULL){
      prev->nextCustomer = NULL;
      (*q)->front = prev;
   }else if (prev == NULL){
      next->prevCustomer = NULL;
      (*q)->rear = next;
   }else{
      next->prevCustomer = prev;
      prev->nextCustomer = next;
   }
   int hours = (currentNode->taskTime);

   free(currentNode);
   (*q)->size--;
   return hours;
}

void freeList (QUEUE **q)
{
   NODE *n = (*q)->rear;
   while ( (*q)->rear != NULL )
   {
      n = ((*q)->rear)->nextCustomer;
      free((*q)->rear);
      (*q)->rear = n;
   }
   free(*q);
}

