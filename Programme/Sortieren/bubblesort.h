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