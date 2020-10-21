#include <stdio.h>

int foo[8];

int main()
{
	for (int i=0;;)
	{
		foo[i] = i++;
		if(i==7) break;
		printf("%i", foo[i]);
	} 
	
}



