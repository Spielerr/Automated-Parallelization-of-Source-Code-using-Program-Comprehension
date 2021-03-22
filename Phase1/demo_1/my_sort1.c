#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    my_sort(n, a);
    
    gettimeofday(&stop, NULL);
    printf("took %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000); 
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // for(int i=0;i<5;i++)
    // {
    //     printf("%d\t", a[i]);
    // }
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    return 0;
}