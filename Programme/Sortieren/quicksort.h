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