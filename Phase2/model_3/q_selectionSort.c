void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
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
        selectionSort(arr, 5);
        printf("%d", is_sorted(arr, 5));
    }
    