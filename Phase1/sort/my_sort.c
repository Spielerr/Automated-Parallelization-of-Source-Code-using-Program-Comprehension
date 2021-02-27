#include <stdio.h>

void sort(int n, int* a)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j] > a[j+1])
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void my_sort(int n, int *a)
{
    int num = 10;
    for(int i=0;i<num;i++)
    {
        // sort(n, a);
    }
    sort(n,a);
}

int main()
{
    int a[] = {2,1,5,3};
    int n = sizeof(a)/sizeof(a[0]);
    printf("%d\n", n);
    my_sort(n, a);
    for(int i=0;i<n;i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}