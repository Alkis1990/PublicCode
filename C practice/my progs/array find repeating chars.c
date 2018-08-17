#include<stdio.h>
#include<stdio_ext.h>
#include<string.h>
#include<stdlib.h>
void main()
{
    char content;
    char array[5000];
    char array_count[5000][2];
    int i=0,j,count=0,a=0,b=0,x=0,y=0,k,l;
    printf("Enter Your Name : ");
    gets(array);
    while(array[i] != '\0')
    {
	for (j=0;array[j] != '\0' ;j++)
	{
	    if (array[i] == array[j])
	    {
		++count;
	    }
	}
	array_count[a][b]=array[i];
	printf("%c Exists in your content ",array_count[a][b]);b++;
	array_count[a][b]=count;
	printf("%d times\n",array_count[a][b]);
        a++;
        b--;
	i++;
	count=0;
    }
}

