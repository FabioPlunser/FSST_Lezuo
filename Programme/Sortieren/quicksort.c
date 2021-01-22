// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specific Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// QuickSort //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define HEADER "Index, DIY Quicksort, qsort, bubblesort"
// creates a array of size size and fills it with random ints in range 0 to max_int
void qs(int *array, int us, int os);
void bsort(int *a, int n);
int *create_array(int MAX_VALUE)
{
	int *array = (int*)malloc(MAX_VALUE * sizeof(int));

	for (int i = 0; i < MAX_VALUE; i++)
	{
		array[i] = rand() % MAX_VALUE;
	}
	return array;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void benchmark(int MAX_VALUE, int meassurepoints)
{
	char quicksort[20];
	char qsortdata[20];
	char bubblesort[20];
	char data[20];
	struct timeval tv_begin, tv_end, tv_diff;

	int csv = open("usage.csv", (O_RDWR | O_TRUNC) | O_CREAT, 0644);
	if (csv == -1){perror("open");}

    write(csv, HEADER, strlen(HEADER));
	write(csv, "\n", 1);
		
	
	int i;
	int *array;
	printf("Time Values\n");
	for(i = 1; i <= meassurepoints; i++)
	{
		array = create_array(MAX_VALUE);
		gettimeofday(&tv_begin, NULL);
		qs(array, 0, MAX_VALUE);
		gettimeofday(&tv_end, NULL);
		printf("DIY Qsort: Sorted Array:\n");
		for(int i=0; i<MAX_VALUE; i++)
		{
			printf("%i,", array[i]);
		}
		printf("\n\n");
		timersub(&tv_end, &tv_begin, &tv_diff);
		sprintf(quicksort, "%ld,", tv_diff.tv_usec);
	
		array = create_array(MAX_VALUE);
		gettimeofday(&tv_begin, NULL);
		qsort(array, MAX_VALUE, sizeof(MAX_VALUE), cmpfunc);
		gettimeofday(&tv_end, NULL);
		printf("QSort: Sorted Array:\n");
		for(int i=0; i<MAX_VALUE; i++)
		{
			printf("%i,", array[i]);
		}
		printf("\n\n");
		timersub(&tv_end, &tv_begin, &tv_diff);
		sprintf(qsortdata, "%ld,", tv_diff.tv_usec);
		
		array = create_array(MAX_VALUE);
		gettimeofday(&tv_begin, NULL);
		bsort(array, MAX_VALUE);
		gettimeofday(&tv_end, NULL);
		printf("BubbleSort: Sorted Array:\n");
		for(int i=0; i<MAX_VALUE; i++)
		{
			printf("%i,", array[i]);
		}
		printf("\n\n");
		timersub(&tv_end, &tv_begin, &tv_diff);
		sprintf(bubblesort, "%ld,", tv_diff.tv_usec);
		
		sprintf(data, "%i,", i);
		write(csv, data, strlen(data));
		write(csv, quicksort, strlen(quicksort));
		printf("DIY Qsort: %sus, " , quicksort);
		write(csv, qsortdata, strlen(qsortdata));
		printf("Qsort: %sus, ", qsortdata);
		write(csv, bubblesort, strlen(bubblesort));
		printf("BubbleSort: %sus\n", bubblesort);
		write(csv, "\n", 1);
	}	
}

int main(int argc, char **argv)
{
	int MAX_VALUE, meassurepoints;
	// create random ints based in current time
	srand(time(NULL));
	

	printf("How many elements should the Array have?: ");
   	scanf("%d",&MAX_VALUE);
	printf("How many measurement points?: ");
   	scanf("%d",&meassurepoints);
	
	
	benchmark(MAX_VALUE, meassurepoints);
	
}
