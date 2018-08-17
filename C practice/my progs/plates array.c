#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>



int generate_alphanumeric(bool is_character)
{
   int k;
   if (is_character == true)
   {
       k=rand()%26;
       k=k+65;
   }
   else
   {
       k=rand()%10;
       k=k+48;
   }
   
   return k;
}



 main()
{
    const int NUMPLATES=3;
    char plates[NUMPLATES][7];
  
    srand(time(NULL));
        
    for (int j=0; j<NUMPLATES; j++)
    {
    
        for (int i=0; i<3; i++)
        {
            plates[j][i]=generate_alphanumeric(true);
            //printf("test1%c\n",plates[j][i]);
        }
        for (int i=3; i<6; i++)
        {
            plates[j][i]=generate_alphanumeric(false);
            
        }
        plates[j][6]='\0';
        printf("%s\n",plates[j]);
    }

    
}

