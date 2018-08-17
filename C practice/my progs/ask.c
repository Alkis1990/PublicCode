
#include <stdio.h>
#include <stdlib.h>
#define min 60
#define hour (60 * min)


main ()
{
   
    unsigned long int t;
    unsigned int hours=0,mins=0,secs=0;
   
    
    
    printf("insert time in seconds\n");
    scanf("%ld",&t);
    
    
    
   // na ftiaksw programa 4.13 page 98

    if (t < 86400 && t!= 0)
    {
        
        hours = t / hour;
        //printf("hours %d\n",hours);
        mins  =(t % hour) / 60 ;
       // printf("mins %d\n",mins);
        secs  = (t % hour) % 60 ; 
        
        printf("time is with hours %d mins %d secs %d\n",hours,mins,secs);
        }

        else if (t == 0)
                printf("you have entered zero time\n");

   
    
 
    
    
        
    
}

