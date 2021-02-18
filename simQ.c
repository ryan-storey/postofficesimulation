#include <simQ.h>
/*---- main function ------------------------------------------*/
int main (int argc, char *argv[])
{
   int		  id;
   QUEUE	 *q = NULL;
   NODE          *node = NULL;
   PARAMETERS    *p = NULL;
   int i;
   int *servicePoints = NULL;
   int totalFulfilled = 0;
   int fulfilled;
   int totalWaitingTime = 0;
   int timedOut = 0;
   int unfulfilled = 0;
   int currentlyServed;
   const gsl_rng_type *T;
   int simNumber = 0;
   int simulations;
   int extraTime = 0;
   gsl_rng *r;
   /* create a random number generator */
   gsl_rng_env_setup();
   T = gsl_rng_default;
   r = gsl_rng_alloc(T);
   /* seed random number generator */
   gsl_rng_set(r,time(0));
   if(argc != 4){
      /* if 3 arguments are not given */
      fprintf(stderr,"Incorrect number of arguments supplied.\n");
      return -2;
   } else{
      /* if second parameter is not a number */
      if(!isdigit(*argv[2])){
         fprintf(stderr,"Number of simulations not provided in arguments.\n");
         return -3;
      }
   }

   /* read in user parameters */
   p = readFromFile(argv[1]);
   q = createQueue(p->maxQueueLength);
   FILE *fp = openFile(argv[3]);
   servicePoints = (int *)createServicePoints(p->numServicePoints);
   /* user-input parameters printed to output file */
   printParameters(argv[3],p);
   simulations = atoi(argv[2]);
   printf("Starting simulation...\n");
   /* begin simulation(s) */
   while(simNumber < simulations){
      simNumber++;
      i = 0;
      fulfilled = 0;
      currentlyServed = 0;
      /* begin individual simulation */
      while((i <= p->closingTime) || (!isQueueEmpty(q) || currentlyServed > 0)){
         i++;
         fulfilled = fulfilCustomers(&servicePoints, p->numServicePoints, &currentlyServed);
         totalFulfilled += fulfilled; 
         serveCustomers(&servicePoints, &q, p->numServicePoints, &totalWaitingTime, &currentlyServed);
         increaseWaitingTimes(&q, &timedOut);
         if(i < p->closingTime)
            newCustomersArrive(&q, &unfulfilled,r, p);
         if(simulations==1){
            /* print current state to file */
            printState(fp,i,currentlyServed,q->size,totalFulfilled,unfulfilled,timedOut);
            if(i == p->closingTime)
               fprintf(fp, "---------THE POST OFFICE HAS CLOSED---------\n\n");
         }
      }
      /* additional time after closing time calculated */
      extraTime += i-p->closingTime;
   }
   
   float avgWaitingTime = totalWaitingTime / (float)totalFulfilled;

   if(simulations == 1){
      fprintf(fp, "It took %d extra time intervals to serve all remaining customers\n", extraTime);
      fprintf(fp, "The average waiting time for fulfilled customers was %f\n",avgWaitingTime);
   }else{
      printAverages(fp, totalFulfilled,unfulfilled,timedOut,avgWaitingTime,extraTime,simulations);
   }
   printf("Simulation finished! Results printed to output file.\n");
   /* free memory */
   freeList(&q);
   free(servicePoints);
   free(p);
   gsl_rng_free(r);
   fclose(fp);
   return 0;
}
