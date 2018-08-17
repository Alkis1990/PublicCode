#include<stdio.h>
#include<string.h>
#include<stdlib.h>


 main()
{
     char input[100];
     int i=0,c;
     
     
    
     
     printf("incert a word\n");
     gets(input);
     
     while (input[i] !='\0')
     {
         c=input[i];
         if (c<=90 && c>=65)
         {
             input[i]=input[i]+32;
         }
         else if (c<=122 && c>=97)
         {
             input[i]=input[i]-32;
         }
     i++;
     }
     
     printf("%s\n",input);
     
}

