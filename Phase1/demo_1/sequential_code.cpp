#include <bits/stdc++.h> 
#include <stdlib.h>
// #include "parallel.h"
#include "sequential_selection.h"

#if 0
void sort(int* a, int n)
{
    
    time_t start, end; 
    time(&start); 
    auto aVector = vectorise(a);
    quicksort(&aVector,0,n-1);
    deVectorise(aVector, a);

    time(&end); 
  
    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    std::cout << "Time taken by program is : " << time_taken << std::setprecision(5); 
    std::cout << " sec " << "\n"; 

    printf("\n");
}
#endif

int main()
{
    // for (int k = 0; k < 10; ++k)
    // {
        
    
    
    int *a = (int *)malloc(50000 * sizeof(int));
    int n = 50000;
    srand(8);
    for(int i = 0; i < n; ++i)
    {   
        
        a[i] = rand();
    }

    // printf("\n%d", RAND_MAX);
    // time_t start, end; 
    // time(&start); 
    auto aVector = vectorise(a, n);
    my_sort(&aVector, 0, n-1);
    deVectorise(aVector, a);

    // time(&end); 
  
    // // Calculating total time taken by the program. 
    // double time_taken = double(end - start); 
    // std::cout << "Time taken by program is : " << time_taken << std::setprecision(5); 
    // std::cout << " sec " << "\n";
    // }
}

