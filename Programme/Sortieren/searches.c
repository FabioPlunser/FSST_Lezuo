void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//program inspired by pseudocode from https://de.wikipedia.org/wiki/Quicksort 
int partition(int *a, int us, int os, int i, int j,  int pivot)
{
	while(i<j)
	{
		while ((i<os)&&(a[i]<pivot))i++;
		while ((j>us)&&(a[j]>=pivot)&&(us<os))j--;
		if (i < j) swap(&a[j], &a[i]);
	}
	if (a[i] > pivot) swap(&a[os], &a[i]);
	
	return i;
}

void qs(int *array, int us, int os)
{
	
	if(us<os)
	{
		int pivot = partition(array, us, os, us, os-1, array[os]);
		
		qs(array, us, pivot-1);
		qs(array, pivot+1, os);
	}
}

void bsort(int *a, int n)
{
	int swapped;

	for(int i = 0; i < n-1; i++)
	{
		swapped = 0;
		for(int j = 0; j < n-i-1; j++)
		{
			if(a[j] > a[j+1])
			{
				swap(&a[j], &a[j+1]);
				swapped = 1;
			}
		}

		if(swapped == 0)
			break;
	}
}