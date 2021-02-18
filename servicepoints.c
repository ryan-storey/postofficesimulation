#include <servicepoints.h>

int *createServicePoints (int quantity)
{
   int *p;
   if ( !( p = (int *)malloc(quantity*sizeof(int)) ) )
   {
      fprintf(stderr,"Out of memory\n");
      exit(1);
   }
   int i;
   for(i=0;i<quantity;i++)
   {
      p[i] = 0;
   }
   return p;
}

int fulfilCustomers(int **servicePoints, int numServicePoints, int *currentlyServed){
   int i=0;
   int fulfilled = 0;
   for(i=0; i<numServicePoints; i++){
      if((*servicePoints)[i]){
          (*servicePoints)[i]--;
          if(!(*servicePoints)[i]){
             fulfilled++;
             (*currentlyServed)--;
          }
      }
   }
   return fulfilled;
}

