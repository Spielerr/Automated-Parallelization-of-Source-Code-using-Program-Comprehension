#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 100;
    int a[n];

    // loop iterations are independent
    for(int i = 0; i<n; ++i)
    {
        a[i] = -1;
    }

    //loop iterations are dependent
    for(int i = 0; i<n; ++i)
    {
        a[i] = a[i] + 5;
    }


    return 0;

}