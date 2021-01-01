// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specific Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// QuickSort //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MY_SIZE 32


void qs(int *array, int us, int os)
{
	int i, j, pivot, temp;

   if(us<os)
   {
      pivot=us;
      i=us;
      j=os;

      while(i<j){
         while((array[i]<=array[pivot])&&(i<os))
            i++;
         while(array[j]>array[pivot])
            j--;
         if(i<j){
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
         }
      }

      temp=array[pivot];
      array[pivot]=array[j];
      array[j]=temp;
      qs(array,us,j-1);
      qs(array,j+1,os);
   }
}

// creates a array of size size and fills it with random ints in range 0 to max_int
int *create_array()
{
	int *array = (int*)malloc(MY_SIZE * sizeof(int));

	for (int i = 0; i < MY_SIZE; i++)
	{
		array[i] = rand() % 50;
	}
	
	return array;
}

int main(int argc, char **argv)
{
	// create random ints based in current time
	srand(time(NULL));
	int *array = create_array();

	for (int i = 0; i < MY_SIZE; i++)
	{
		printf("Random Int: %i\n", array[i]);
	}
	qs(array, 0, MY_SIZE);
	for (int i = 0; i < MY_SIZE; i++)
	{
		printf("Sorted: %i\n", array[i]);
	}
	// for(int i=0; i<MY_SIZE; i++)
	// {
	// 	printf("Random Int: %i\n", a[i]);
	// }
}
