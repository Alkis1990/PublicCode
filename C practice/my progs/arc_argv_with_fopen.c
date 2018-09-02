#include<stdio.h>
//#include<string.h>
#include<stdlib.h>
#include<time.h>
//#include <stdbool.h>



    
int main(int argc, char *argv[])
{
    srand(time(NULL));
    
     FILE *fp;
     int j;
     
     fp=fopen(argv[4],"w");
     
   
   if(fp==NULL)
   {
       puts("error while opening file");
       exit(2);
   }
   else
   
           if (argc==5)
           
           {
               
           
                for (j=0; j<atoi(argv[2]); j++)
                {
                    for (int i=0; i<atoi(argv[1]); i++)
                         {
                            fprintf(fp,"%d",rand()%10);
                         
                              if (i%atoi(argv[3])==0 && i!=1)
                              {
                                    fputs("\n",fp);
                              }
                         }
                                            
                }
                         
   }
    
   fclose(fp);
return 0;
   
}


    
    
   
  
   

