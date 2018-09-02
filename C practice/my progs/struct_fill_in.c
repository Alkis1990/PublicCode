#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>



int fill_plates(bool is_character)
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

char* fill_colour()
{
   int k;
   static char chosen_colour[10];
   
       k=rand()%10;
       
   switch (k)
   {
   
       case 0:
           strcpy(chosen_colour,"RED");
           break;
       case 1:
           strcpy(chosen_colour,"BLACK");
           break;
       case 2:
           strcpy(chosen_colour,"YELLOW");
           break;
       case 3:
           strcpy(chosen_colour,"GREEN");
           break;
       case 4:
           strcpy(chosen_colour,"PURPLE");
           break;
       case 5:
           strcpy(chosen_colour,"BLUE");
           break;
       case 6:
           strcpy(chosen_colour,"GREY");
           break;
       case 7:
           strcpy(chosen_colour,"NIKEL");
           break;
       case 8:
           strcpy(chosen_colour,"BROWN");
           break;
       case 9:
           strcpy(chosen_colour,"GOLD");
           break;
       default:
           strcpy(chosen_colour,"WHITE");
           break;
   }
   
   return chosen_colour;
   
}



 main()
{
     struct data
     {
         char plate[7];
         char colour[10];
         char maker[15];
         int ccs;
         int hps;
         
         
     }pelates[10];
     
     
    srand(time(NULL));
        
    for (int j=0; j<5; j++)
    {
    
        for (int i=0; i<3; i++)
        {
            pelates[j].plate[i]=fill_plates(true);
            
        }
        for (int i=3; i<6; i++)
        {
            pelates[j].plate[i]=fill_plates(false);
            
        }
        pelates[j].plate[6]='\0';
        printf("%s\n",pelates[j].plate);
    }
    
    printf("====================\n");

    for (int j=0; j<5; j++)
    {
        
        
        strcpy(pelates[j].colour,fill_colour());
            
        
        printf("%s\n",pelates[j].colour);
    }
    
}


