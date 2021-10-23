void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)     
 
       // Last i elements are already in place  
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
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
        bubbleSort(arr, 5);
        printf("%d", is_sorted(arr, 5));
    }
    