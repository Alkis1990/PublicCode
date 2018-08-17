#include "stdio.h"
#include "stdlib.h"

char input;
int len,dep,j;

void length (int len)
{
    int i;
    for (i=1; i<=len; i++)
    {
    
        printf("%c",input);
    }
    printf("\n");
    
}

void depth (int dep)
{
    printf("%c",input);
    int i;
    for (i=2;i<=len-1;i++)
    {
        printf(" ");
    }
    printf("%c\n",input);
}

main()
{

    
    printf("incert a character\n");
    scanf("%c",&input); 
    
    printf("how many rows?\n");
    scanf("%d",&len); 
    printf("how many collums?\n");
    scanf("%d",&dep);
    
    if (dep==1)
        length(len);
    
    if (dep==2)
        length(len);
        length(len);
        
    if (dep>=3)
        //length(len);
        for (j=1;j<=dep-2;j++)
            depth(dep);
        
        length(len);
        
    
    
    
    
    
}
