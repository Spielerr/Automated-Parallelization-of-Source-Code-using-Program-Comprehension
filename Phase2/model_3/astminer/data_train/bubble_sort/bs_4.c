

void BubbleSort(int arr[], int n)
{
	int i,j;
	int temp;

	for(i=0; i<n-1; i++)
	{
		for(j=0; j<n-1-i; j++)
		{
			if(arr[j+1]<arr[j])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

