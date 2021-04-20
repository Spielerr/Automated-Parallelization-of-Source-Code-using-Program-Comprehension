// optimized code

#include <stdio.h>
#include <omp.h>
#include <parallel/numeric>
double mean(int const *a1, int n1) {
   double* s;
   __gnu_parallel::partial_sum( a1, a1 + n1, s );
   return *s/n1;
}

#include <parallel/algorithm>
void sort(int *arr, int const arr_n) {
   __gnu_parallel::sort(arr, arr + arr_n );
}

int max(int *a4, int n4) {
   return *__gnu_parallel::max_element(a4, a4 + n4 );
}

int min(int * const a4, int const n4) {
   return *__gnu_parallel::min_element(a4, a4 + n4 );
}

int main() {
   int arr1[5] = {2, 1, 3, 6, 5};
   int arr2[5] = {2, 0, 3, 6, 5};
   int n = sizeof(((arr1))) / sizeof(((arr1[0])));
   sort(arr1, n);
   #pragma omp parallel sections 
   {
      #pragma omp section 
      int min1 = min(arr1, n);
      #pragma omp section 
      int max1 = max(arr1, n);
   }
}

