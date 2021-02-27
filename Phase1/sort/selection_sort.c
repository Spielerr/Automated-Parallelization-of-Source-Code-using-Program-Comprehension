#include<stdio.h>
#include<stdlib.h>

void selection_sort(int *a, int n)
{
    for(int i = 0;i<n-1;++i)
    {
        int min = i;
        for(int j = i+1;j<n;++j)
        {
            if(a[j]<a[min])
            {
                min = j;
            }
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

int main()
{
    int a[] = {5,3,6,1,77};
    int n = 5;
    for(int i = 0;i<5;++i)
    {
        printf("%d ",a[i]);
    }

    printf("\n");
    selection_sort(a,n);

    for(int i = 0;i<5;++i)
    {
        printf("%d ",a[i]);
    }

    printf("\n");

}