//einai ask.12.1 ...den exei teliosei

#include<stdio.h>
#include<stdio_ext.h>
#include<string.h>
#include<stdlib.h>
void main()
{
    char lexi1[80];
    char lexi2[80];
    char temp;
    
    int i=0,j,count=0,k=0;
    
    printf("Enter array_1: ");
    gets(lexi1);
    printf("Enter array_2: ");
    gets(lexi2);
    
    int s=strlen(lexi1);
    
    while(lexi1[i] != '\0')
    {
	for (j=0;lexi2[j] != '\0' ;j++)
	{
	    if (lexi1[i] == lexi2[j])
	    {
		++count;
	    }
	}
	if (count)
	{
            printf("--------------------------\n");
            printf("task1\n");
            printf("%c Exists in your content ",lexi1[i]);
            printf("%d times\n",count);
           
            i=k;
            while (lexi1[k] !='\0')
            {
                if(k==s)
                {
                    lexi1[k]=NULL;
                    k++;
                }
                else
                {
                lexi1[k]=lexi1[k+1];
                k++;
                }
            
            }
            
	}
	i++;
	count=0;
    }


    printf("--------------------------\n");
    printf("task2\n");
    printf("%s\n",lexi1);
}

