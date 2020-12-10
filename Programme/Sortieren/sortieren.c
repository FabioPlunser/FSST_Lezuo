#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void qs(int *a, int us, int os)
{
	int i,j, pivot, temp;

	if (us<os)
	{
		pivot=us;
		i=us;
		j=os;
		while(i<j)
		{
			while(a[i]<=a[pivot]&&i<os) i++;
			while(a[j]>a[pivot]) j--;

			if(i<j)
			{
				temp=a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	temp=a[pivot];
	a[pivot]=a[j];
	a[j]=temp;
	qs(a, us, j-i);
	qs(a, j+1, os);
}

// creates a array of size size and fills it with random ints in range 0 to max_int
int *create_array(int size, int max_int)
{
	int *b = (int*)malloc(size * sizeof(int));

	for (int i=0; i<size; i++) {
		b[i] = rand() % max_int;
	}

	return b;
}

#define MY_SIZE 32

int main(int argc, char **argv)
{
	// create random ints based in current time
	srand(time(NULL));

	int *a = create_array(MY_SIZE, 100);

	qs(a, 0, MY_SIZE);

	int old = -1;
	for (int i=0; i<MY_SIZE; ++i)      {
		if (old != -1) assert(old <= a[i]);
		printf("%d ", a[i]);
		old = a[i];
	}
	printf("\n");
}
