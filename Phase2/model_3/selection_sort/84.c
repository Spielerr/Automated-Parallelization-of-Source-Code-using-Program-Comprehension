



void swap(int *a, int *b);

void selectionSort(int arr[], int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = i; j < size; j++)
		{
			if (arr[i] > arr[j])
				swap(&arr[i], &arr[j]);
		}
	}
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

