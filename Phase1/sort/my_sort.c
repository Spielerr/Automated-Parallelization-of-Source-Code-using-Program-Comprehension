#include <stdio.h>

void sort(int n, int* a2)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a2[j] > a2[j+1])
            {
                int temp = a2[j];
                a2[j] = a2[j+1];
                a2[j+1] = temp;
            }
        }
    }
}

void my_sort(int n1, int n2, int *a1, int *a2)
{
    int num = 10;
    for(int i=0;i<num;i++)
    {
        // sort(n, a);
    }
    sort(n1,a1);
}

int main()
{
    int my_array[] = {2,1,5,3};
    int my_array2[] = {2,1,5,3,2};
    int n = sizeof(my_array)/sizeof(my_array[0]);
    printf("%d\n", n);
    my_sort(n, n, my_array, my_array2);
    for(int i=0;i<n;i++)
    {
        printf("%d\t", my_array[i]);
    }
    printf("\n");
    return 0;
}