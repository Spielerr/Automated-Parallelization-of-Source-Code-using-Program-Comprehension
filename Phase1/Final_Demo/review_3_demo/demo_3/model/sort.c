void sort(int* arr,const int arr_n, int fn_call_no)
{
	for(int i = 0; i < arr_n-1; ++i)
	{
		int min = i;
		for(int j = i+1;j < arr_n;++j)
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
