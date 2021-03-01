#include <stdio.h>
#include <stdlib.h>

void sort(int n, int* a)
{
    for (int i = n - 1; i > 0; --i)
    {
        int max = i;
        for (int j = i - 1; j >= 0; --j)
        {
            if ((a)[j] > (a)[max])
            {
                max = j;
            }
        }
        int temp = a[i];
        a[i] = a[max];
        a[max] = temp;
    }
}

void my_sort(int n, int *a)
{
    int num = 3;
    for(int i=0; i<num; i++)
    {
        // sort(n, a);
    }
    sort(n, a);
}

int main()
{
    int *a = (int *)malloc(50000 * sizeof(int));
    int n = 50000;
    srand(8);
    for(int i = 0; i < n; ++i)
    {   
        
        a[i] = rand();
    }
    for(int i=0;i<5;i++)
    {
        printf("%d\t", a[i]);
    }
    // printf("Array length = %d\n", n);
    my_sort(n, a);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    for(int i=0;i<5;i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}