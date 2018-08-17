#include "stdio.h"
#include "stdlib.h"

unsigned int number,start=1,results;


void total (number)
{
    while (start<=number)
    {
        results=results+start;
    ++start;
    }
    //return results;
}

main(){
    
    printf("enter an integer\n");
    scanf("%d",&number);
    
   total(number);
    
    printf("your results are %d\n",results);
}
    
