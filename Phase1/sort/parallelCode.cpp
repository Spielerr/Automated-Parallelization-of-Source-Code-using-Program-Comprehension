#include <bits/stdc++.h> 
#include "parallel.h"

int main()
{
    // int a[] = {5,2,8,1,9};
    // int n = 5;
    int a[231423];
    int n = 231423;
    for(int i=0;i<n;i++)
    {
        a[i] = n-i;
    }
    
    // for(int i = 0;i<5;++i)
    // {
    //     printf("%d ",a[i]);
    // }

    printf("\n");
    time_t start, end; 
    time(&start); 
    auto aVector = vectorise(a);
    quicksort(&aVector,0,n-1);
    deVectorise(aVector, a);

    time(&end); 
  
    // Calculating total time taken by the program. 
    double time_taken = double(end - start); 
    std::cout << "Time taken by program is : " << std::fixed  << time_taken << std::setprecision(5); 
    std::cout << " sec " << "\n"; 

    // for(int i = 0;i<5;++i)
    // {
    //     printf("%d ",a[i]);
    // }

    printf("\n");
}

