#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
 
int test(int a)
{
    return a + 2;
}
 
void add(int *a, int *b)
{
    *a = *a + 1;
    *b = *b + 1;
}
 
int add_with_return(int *test_v1, int *test_v2)
{
    *test_v1 = *test_v1 + 1;
    *test_v2 = *test_v2 + 2;
    return 1;
}
 
int main(int argc, const char** argv)
{
   int *t1 = (int*)malloc(sizeof(int));
   *t1 = 2;
   int *t2 = (int*)malloc(sizeof(int));
   *t2 = 4;
   int *a = (int*)malloc(sizeof(int));
   *a = 23;
   int *b = (int*)malloc(sizeof(int));
   *b = 123;
 
   int res = add_with_return(t1,t2);
   add(a,b);
 
   int res2 = res + 1;
 
   int sum_value = *t1 + *t2 + *a;
   printf("Final res value: %d\n", res);
   printf("Final res2 value: %d\n", res2);
   printf("Final sum_value value: %d\n", sum_value);
}
