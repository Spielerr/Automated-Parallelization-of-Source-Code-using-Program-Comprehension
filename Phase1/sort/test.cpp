#include <iostream>

void sort(int a, int n) {}

int main()
{
    int a[] = {5,2,8,1,9};
    sort(a,5);
    for(int i = 0;i<5;++i)
    {
        printf("%d ",a[i]);
    }

    printf("\n");
}
