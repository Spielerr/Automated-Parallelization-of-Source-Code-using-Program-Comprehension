#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
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

int my_max(int *a4, int n4) {
   int max = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] > max) {
         max = a4[i];
      }
   }
   printf("Max : %d\n", max);
   
   return 1;
}

int my_min(int *a4, int n4) {
   int min = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] < min) {
         min = a4[i];
      }
   }
   printf("Min : %d\n", min);
   
   return 1;
}

int main(int argc, char **argv) {
   struct timeval stop, start;
   gettimeofday(&start, 0);
   int input_n = 30000;
   int *arr1 = (int *) malloc(input_n * sizeof(int));
   int array_size1 = input_n;
   srand(8);
   for(int i = 0; i < array_size1; ++i) {
      arr1[i] = rand();
   }
   int *arr2 = (int *) malloc(input_n * sizeof(int));
   int array_size2 = input_n;
   srand(2);
   for(int i = 0; i < array_size2; ++i) {
      arr2[i] = rand();
   }
   int n = array_size1;
   sort(arr1, n);
   #pragma omp parallel sections 
   {
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      sort(arr2, n);
      #pragma omp section 
      my_min(arr2, n);
      #pragma omp section 
      my_max(arr2, n);
      sort(arr1, n);
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      sort(arr2, n);
      #pragma omp section 
      my_min(arr2, n);
      #pragma omp section 
      my_max(arr2, n);
      sort(arr1, n);
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      sort(arr2, n);
      #pragma omp section 
      my_min(arr2, n);
      #pragma omp section 
      my_max(arr2, n);
      sort(arr1, n);
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      sort(arr2, n);
      #pragma omp section 
      my_min(arr2, n);
      #pragma omp section 
      my_max(arr2, n);
      sort(arr1, n);
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      sort(arr2, n);
      #pragma omp section 
      my_min(arr2, n);
      #pragma omp section 
      my_max(arr2, n);
      sort(arr1, n);
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      sort(arr2, n);
      #pragma omp section 
      my_min(arr2, n);
      #pragma omp section 
      my_max(arr2, n);
      gettimeofday(&stop, 0);
      printf("Time Taken : %lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000);
   }
}
