#include <parallel/algorithm>
#include <parallel/numeric>
#include <stdio.h>
void sort(int *arr, int n)
{
    __gnu_parallel::sort(arr, arr + n);
}

int main()
{
    int arr[] = {10,40,20,30,50};
    int n = 5;
    for(int i = 0; i<n; ++i)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    sort(arr, n);
    for(int i = 0; i<n; ++i)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

	