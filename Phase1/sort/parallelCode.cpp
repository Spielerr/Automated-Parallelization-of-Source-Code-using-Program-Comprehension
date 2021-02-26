#include <iostream>
#include "parallel.h"

int main()
{
    int a[] = {5,2,8,1,9};
    int n = 5;
    
    for(int i = 0;i<5;++i)
    {
        printf("%d ",a[i]);
    }

    printf("\n");

    auto aVector = vectorise(a);
    quicksort(aVector,n,0);
    deVectorise(aVector, a);

    for(int i = 0;i<5;++i)
    {
        printf("%d ",a[i]);
    }

    printf("\n");
}

