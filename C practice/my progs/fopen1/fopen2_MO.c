#include<stdio.h>
//#include<string.h>
#include<stdlib.h>
//#include<time.h>
//#include <stdbool.h>

main()
{
    
   FILE *fp1,*fp2;
   
   int sum,temp,count=0;
   float mo;
   
   
   fp1=fopen("/home/alkiviadis/Desktop/input.txt","r");
   fp2=fopen("/home/alkiviadis/Desktop/output.txt","w");
   
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
                printf("numbers counted %d\n",count);
                printf("numbers red from file %d\n",temp);

                sum=sum+temp;
                
                printf("++++++++++++++++++\n");
                printf("sum is %d\n",sum);
                printf("==================\n");
                count++;
                temp=0;
            if (feof(fp1)) break;
       }         
       fprintf(fp2,"total sum is %d\n",sum);
       mo=sum/count;
       fprintf(fp2,"mo is %f\n",mo);
   }
   
   
   
    
    
   fclose(fp1);
   fclose(fp2);
}





