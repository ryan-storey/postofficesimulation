#include <filehandling.h>

void printState(FILE *fp, int time, int currentlyServed, int queueSize, int fulfilled, int unfulfilled, int timedOut)
{
   fprintf(fp,"Time Interval Number: %d\nCustomers currently being served: %d\n"
              "Currently in queue: %d\nFulfilled: %d\nUnfulfilled: %d\n"
              "Timed Out: %d\n\n",
              time, currentlyServed, queueSize, fulfilled, unfulfilled,
              timedOut);
}

FILE *openFile(char *fileName)
{
   FILE *fp;
   if ((fp = fopen(fileName, "a")) == NULL )
   {
      printf("Unable to open file for write access.\n");
      fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
      exit(1);
   }
   return fp;
}

void printParameters(char *fileName, PARAMETERS *p)
{
   FILE *fp;
   if ((fp = fopen(fileName, "w")) == NULL )
   {
      printf("Unable to open file for write access.\n");
      fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
      exit(1);
   }
   fprintf(fp,"Max Queue Length: %d\nNum Service Points: %d\n"
           "Closing Time: %d\nAverage Customers Per Interval: %d\n"
           "Standard Deviation of New Customers: %d\n"
           "Average Patience: %d\nStandard Deviation of Patience: %d\n"
           "Average Task Time: %d\nStandard Deviation of Task Time: %d\n\n",
           p->maxQueueLength,
           p->numServicePoints,
           p->closingTime,
           p->meanCustomers,
           p->sdNewCustomers,
           p->meanPatience,
           p->sdPatience,
           p->meanTaskTime,
           p->sdTaskTime);
   fclose(fp);
}

void printAverages(FILE *fp, int fulfilled, int unfulfilled, int timedOut, float avgWaitingTime,int extraTime, int simulations)
{
   float avgFulfilled = fulfilled / (float) simulations;
   float avgUnfulfilled = unfulfilled / (float) simulations;
   float avgTimedOut = timedOut / (float) simulations;
   float avgExtraTime = extraTime / (float) simulations;
   fprintf(fp, "For %d simulations, the average number of fulfilled customers was %f\n",simulations,avgFulfilled);
   fprintf(fp, "For %d simulations, the average number of unfulfilled customers was %f\n",simulations,avgUnfulfilled);
   fprintf(fp, "For %d simulations, the average number of timed-out customers was %f\n",simulations,avgTimedOut);
   fprintf(fp, "For %d simulations, the average waiting time per fulfilled customer was %f\n",simulations,avgWaitingTime);
   fprintf(fp, "For %d simulations, the average extra time to fulfil customers after closing was %f\n",simulations,avgExtraTime);
}

