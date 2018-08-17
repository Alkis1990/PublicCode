#include "stdio.h"
#include "stdlib.h"

main()
{
    int a,b,c,*p1,*p2,*p3;
    
    p1=&a;
    p2=&b;
    p3=&c;
    
    scanf("%d",p1);
    scanf("%d",p2);
    
    p3=*p1+*p2;
    
    printf("apotelesma %d\n",p3);
    
    
    
    
    
}
