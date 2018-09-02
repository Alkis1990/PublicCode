#include<stdio.h>
//#include<string.h>
#include<stdlib.h>
//#include<time.h>
//#include <stdbool.h>

main()
{
    
   FILE *fp;
   
   fp=fopen("/home/alkiviadis/Desktop//fopen1/arithmoi.txt","w");
   
   for (int i=1; i<=100; i++)
   {
       fprintf(fp,"%d ",i);
       if (i%10==0)
       {
           fprintf(fp,"\n");
       }
   }
   
    
    
   fclose(fp); 
}





