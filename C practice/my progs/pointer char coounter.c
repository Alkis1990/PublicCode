#include "stdio.h"
#include "stdlib.h"

main()
{
    char *p;
    int counter=0;
    
    
    p="anraki aspro kai paxi";
    
    
    while (*p != '\0')
    {
        if (*p =='a') {
            ++counter;
	}
        ++p;
    }
    
    printf("exei %d grammata\n",counter);
}
