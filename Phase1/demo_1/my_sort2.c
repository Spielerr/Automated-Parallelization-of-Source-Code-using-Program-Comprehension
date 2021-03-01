#include <stdio.h>
#include <stdlib.h>

//insertion sort
void sort(int n, int* a)
{
    int i, key, j; 
    for (i = 1; i < n; i++)
    { 
        key = a[i]; 
        j = i - 1; 
 
        while (j >= 0 && a[j] > key)
        { 
            a[j + 1] = a[j]; 
            j = j - 1; 
        } 
        a[j + 1] = key; 
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