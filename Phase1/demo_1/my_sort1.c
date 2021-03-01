#include <stdio.h>
#include <stdlib.h>

//selection sort
void sort(int n, int* a)
{
    int i, j, min_idx; 
  
    for (i = 0; i < n-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (a[j] < a[min_idx]) 
            min_idx = j; 
  
        int temp = a[min_idx];
        a[min_idx] = a[i];
        a[i] = temp;
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