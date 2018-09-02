#include<stdio.h>
//#include<string.h>
#include<stdlib.h>
//#include<time.h>
//#include <stdbool.h>

main()
{
    
   FILE *fp1,*fp2;
   
   int min,max,temp;
   int count=0;
   
   min=max=temp;
   
   
   fp1=fopen("/home/alkiviadis/Desktop/input.txt","r");
   fp2=fopen("/home/alkiviadis/Desktop/output.txt","a");
   
   if(fp1==NULL)
   {
       puts("error while opening file");
       exit(2);
   }
   else
   {
   
       while (1)
       
       {
                fscanf(fp1,"%d",&temp);
                //printf("numbers counted %d\n",count);
                //printf("numbers red from file %d\n",temp);
                if (temp<min) min=temp;
                if (temp>max) max=temp;
                
                
                //count++;
                temp=0;
                
            if (feof(fp1)) break;
       }     
       fprintf(fp2,"min %d max %d\n",min,max);
       
   }
   
    
   fclose(fp1);
   fclose(fp2);
}





