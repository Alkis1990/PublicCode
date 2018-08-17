

//#include <stdlib.h> 
#include <stdio.h>
//#include <math.h>


 main ()
{
     char xaraktires=32;
     int metritis=0;
     
     
     while (xaraktires <=255)
     {
         printf("%d xaraktires",xaraktires);
         ++metritis;
         ++xaraktires;
         if (metritis % 30 ==0) 
             printf("\n");
     }
   
    // printf("%d xaraktires\n",metritis);
     
}
 

 