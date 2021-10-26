void sort(int* arr,const int arr_n, int k)
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


    
    #include <stdio.h>
    int is_sorted(int *a, int n)
    {
        for(int i=1; i<n; ++i)
        {
            if(a[i-1] > a[i])
            {
                return 0;
            }
        }
        return 1;
    }

    int main()
    {
        int arr[] = {1,6,2,8,5};
        sort(arr, 5);
        printf("%d", is_sorted(arr, 5));
    }
    