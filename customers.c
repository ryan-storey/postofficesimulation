#include <customers.h>
#include <stdio.h>

/* add new customers to the queue */
void newCustomersArrive(QUEUE **q, int *unfulfilled, gsl_rng *r, PARAMETERS *p)
{
   int i;
   int n;
   NODE *node = NULL;
   do
   {
      /* generate a positive number of customers to be added */
      n = gsl_ran_gaussian(r,p->sdNewCustomers)+p->meanCustomers;
   } while (n<0);

   for(i=0;i<n;i++)
   {
      /* if there is space in the queue, add new customer */
      if(!isQueueFull(*q))
      {
         node = newNode(i);
         do
         {
            /* generate random values greater than zero */
            node->maxWaitingTime = gsl_ran_gaussian(r,p->sdPatience)+p->meanPatience;
            node->taskTime = gsl_ran_gaussian(r,p->sdTaskTime)+p->meanTaskTime;
         } while (node->taskTime < 1 || node->maxWaitingTime < 1);
         enqueue(q, node);

      } else {
         (*unfulfilled)++;
      }
   }
}

/* increase the time waited for each customer in queue by 1 */
void increaseWaitingTimes(QUEUE **q, int *timedOut)
{
   int i = 0;
   NODE *currentNode = (*q)->front;
   NODE *tempNode = NULL;
   /* loop through each node */
   while(currentNode != NULL)
   {
      (currentNode->waitingTime)++;
      tempNode = currentNode->prevCustomer;
      /* if max waiting tolerance limit is hit, remove from queue */
      if(currentNode->waitingTime == currentNode->maxWaitingTime)
      {
         dequeue(i, q);
         (*timedOut)++;
      }
      currentNode = tempNode;
   }
}

/* serve customers who are at front of the queue */
void serveCustomers(int **servicePoints, QUEUE **q, int numServicePoints, int *totalServingTime, int *currentlyServed)
{
   int i=0;
   int servingTime = 0;
   for(i=0;i<numServicePoints; i++)
   {
      if(!isQueueEmpty(*q)){
         /* if service point is empty, dequeue customer */
         if((*servicePoints)[i] == 0)
         {
             servingTime = dequeue(0, q);
             *totalServingTime += servingTime;
             (*servicePoints)[i] = servingTime;
             (*currentlyServed)++;
         }
      }
   }
}







