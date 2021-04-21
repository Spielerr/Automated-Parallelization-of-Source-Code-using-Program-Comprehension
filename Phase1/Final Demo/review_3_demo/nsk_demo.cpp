#include <stdio.h>

double mean(const int* a1, int n1)
{
    double mean = 0;
    for(int i = 0;i<n1;++i)
    {
        mean += a1[i];
    }
    mean /= n1;
    return mean;
}

void sort(int* arr,const int arr_n)
{
    for(int i = 0;i<arr_n-1;++i)
    {
        int min = i;
        for(int j = i+1;j<arr_n;++j)
        {
            if(arr[j]<arr[min])
            {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}


int max(int* a4, int n4)
{
    int max = a4[0];
    for(int i = 1; i<n4; ++i)
    {
        if(a4[i]>max)
        {
            max = a4[i];
        }
    }

    return max;
}

int min(int* const a4, const int n4)
{
    int min = a4[0];
    for(int i = 1; i<n4; ++i)
    {
        if(a4[i]<min)
        {
            min = a4[i];
        }
    }

    return min;
}



int main()
{
    int arr1[] = {2, 1, 3, 6, 5};
    int arr2[] = {2, 0, 3, 6, 5};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    sort(arr1, n);
    int min1 = min(arr1, n);
    int max1 = max(arr1, n);
    
    return 0;
}
