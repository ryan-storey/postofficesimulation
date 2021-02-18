#include <parameters.h>
/* read user input parameters from file */
PARAMETERS *readFromFile(char *fileName)
{
   FILE *fp;
   char ch[50];
   int value;
   if ( (fp = fopen(fileName, "r")) == NULL )
   {
      fprintf(stderr, "Unable to open file for read access.\n");
      exit(1);
   }

   PARAMETERS *p = (PARAMETERS *)malloc(sizeof(PARAMETERS));
   if ( p==NULL )
   {
      fprintf(stderr,"Insufficient memory\n");
      exit(-3);
   }

   while (!feof(fp))
   {
      fgets(ch, sizeof(ch), fp);
      if(ch[0] == '#' || ch[0] == '\0') continue;
      if(sscanf(ch, "maxQueueLength %d", &value) == 1){
         checkIfValid(value);
         p->maxQueueLength = value;
      }else if (sscanf(ch, "numServicePoints %d", &value) == 1){
         checkIfValid(value);         
         p->numServicePoints = value;
      }else if (sscanf(ch, "closingTime %d", &value)==1){
         checkIfValid(value);
         p->closingTime = value;
      }else if (sscanf(ch, "averageNewCustomersPerInterval %d", &value)==1){
         checkIfValid(value);         
         p->meanCustomers = value;
      }else if (sscanf(ch, "sdNewCustomersPerInterval %d", &value)==1){
         checkIfValid(value);
         p->sdNewCustomers = value;
      }else if (sscanf(ch, "averageCustomerPatience %d", &value)==1){
         checkIfValid(value);         
         p->meanPatience = value;
      }else if (sscanf(ch, "sdCustomerPatience %d", &value)==1){
         checkIfValid(value);
         p->sdPatience = value;
      }else if (sscanf(ch, "averageTaskTime %d", &value)==1){
         checkIfValid(value);
         p->meanTaskTime = value;
      }else if (sscanf(ch, "sdTaskTime %d", &value)==1){
         checkIfValid(value);         
         p->sdTaskTime = value;
      }
   }

   fclose(fp);
   return p;
}

void checkIfValid(int value){
   if(value < 0){
      fprintf(stderr, "Invalid parameter value in file, all values must be 0 or higher\n");
      exit(3);
   }
}



