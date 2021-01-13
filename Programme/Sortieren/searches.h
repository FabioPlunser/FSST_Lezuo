void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *array, int us, int os, int pivot)
{	
	while(us<os){
		while((array[us]<=array[pivot])&&(us<os)) us++;
		while(array[os]>array[pivot]) os--;
		if(us<os) swap(&array[us], &array[os]);	
	}
	swap(&array[pivot], &array[os]);
}

void qs(int *array, int us, int os)
{
	int pivot = os;
	if(us<os)
	{
		partition(array, us, os, os);
		
		qs(array, us, pivot-1);
		qs(array, pivot+1, pivot);
	}
}

// int partition(int *a, int us, int os)
// {
// 	int i, piv;

// 	/* set pivot */
// 	piv = a[os];
// 	i = us - 1;

// 	for(int j = us; j < os; j++)
// 	{
// 		if(a[j] < piv)
// 		{
// 			i++;
// 			swap(&a[i], &a[j]);
// 		}
// 	}
// 	swap(&a[i+1], &a[os]);

// 	return (i+1);
// }
// void qs(int *a, int us, int os)
// {
// 	int pi;

// 	if(us < os)
// 	{
// 		pi = partition(a, us, os);

// 		qs(a, us, pi-1);
// 		qs(a, pi+1, os);
// 	}
// }


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