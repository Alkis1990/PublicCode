#include<stdio.h>
//#include<string.h>
#include<stdlib.h>
//#include<time.h>
//#include <stdbool.h>



    double par (double n)
    {
     if(n <= 1)
     {
      returna 1;
     }
     return n + par(1/(n - 1));
        
    }
  

int  main() {
   double n = 2;
   par(n);
   printf("outpoot N %f\n" ,par(n));
   return 0;
}

   
    

