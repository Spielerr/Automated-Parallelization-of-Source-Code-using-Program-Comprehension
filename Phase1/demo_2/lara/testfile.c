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


// int median(int* a2, int n2)
// {
// sort(a2,n2);

// if (n2 % 2 != 0)
// {
// return a2[n2 / 2];
// }

// return (a2[(n2 - 1) / 2] + a2[n2 / 2]) / 2.0;

// }


int search(int *a3, int n3, int key)
{
    for(int i = 0;i<n3;++i)
    {
        if(a3[i]==key)
        {
            return i;
        }
    }
    return -1;
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

int factorial(int n)
{
    int prod=1;
    for(int i=n;i>=1;i--)
    {
        prod*=i;
    }
    return prod;
}


int main()
{
    // int num = 10;
    // int fact = factorial(num);
    // int array[] = {1,2,3,4,5};
    // int array_size = sizeof(array)/sizeof(array[0]);
    // double m1 = mean(array, array_size);
    // //int m2 = median(array, array_size);
    // sort(array, array_size);
    // int m3 = max(array, array_size);
    // int m4 = min(array,array_size);
    // //int k = search(array,array_size,4);

    int arr1[] = {2, 1, 3, 6, 5};
    int arr2[] = {2, 0, 3, 6, 5};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    sort(arr1, n);
    int min1 = min(arr1, n);
    int max1 = max(arr1, n);

    sort(arr2, n);
    int min2 = min(arr2, n);
    int max2 = max(arr2, n);


    return 0;
}

/*
main; arr; [sort max min]
main; arrsize; [max min]
main; n; [max]

sort(arr)
    min(arr)
    max(arr)
    mean(arr)
---------

sort(arr)
min(arr)

data dependencies
arr being changed only in sort
return arr as key with sort fn call, line number

ex=> arr: sort

separate list: fn calls and the corresponding line numbers

take care of global variables
global variables: fns writing into it



#pragma omp parallel sections
   {
   
   

    #pragma omp section
    {
        sort(array, array_size);

        #pragma omp section
        {
            int m3 = max(array, array_size);
    
            int m4 = min(array, array_size);
        }

    }
   
   
   
   }

*/