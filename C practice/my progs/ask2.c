#include "stdio.h"
#include "stdlib.h"

int a,b,c;
float mo,result;

main(){
    printf("enter 3 number with coma betwin\n");
scanf("%d,%d,%d",&a,&b,&c);

if (a==1)
{
        result=b+c;
    
}       
    else if (a==2) 
    {

        if (b==0) 

            printf("you tried to divine by zero\n");

        else

            result=b/c;

    }
    else if (a==3) 
    {
        mo=(b+c)/2;
        result=mo;

    }
else
{
    printf("error, wrong input");
        
}

printf("your results are %f\n",result);
}
