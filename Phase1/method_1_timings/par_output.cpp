// parallelized code

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
int binarySearch(int arr[], int l, int r, int x) {
   // int binarySearch(int arr[], int l, int r, int x,  int fn_call_no)
   while(l <= r) {
      int m = l + (r - l) / 2;
      if(arr[m] == x) {
         // printf("Index : %d\n", m);
         
         return 1;
      }
      if(arr[m] < x) l = m + 1;
      else r = m - 1;
   }
   
   return -1;
}

int countOccurrences(int arr[], int n, int x) {
   // int countOccurrences(int arr[], int n, int x, int fn_call_no)
   int res = 0;
   for(int i = 0; i < n; i++) if(x == arr[i]) res++;
   // printf("Min Occurence of %d : %d\n", x, res);
   
   return 1;
}

int ceilSearch(int arr[], int low, int high, int x) {
   int i;
   if(x <= arr[low]) 
   return low;
   for(i = low; i < high; i++) {
      if(arr[i] == x) 
      return i;
      if(arr[i] < x && arr[i + 1] >= x) 
      return i + 1;
   }
   
   return -1;
}

#include <parallel/numeric>
double mean(int const *a1, int n1, int fn_call_no) {
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
   // printf("Max : %d\n", max);
   
   return 1;
}

int my_min(int *a4, int n4) {
   int min = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] < min) {
         min = a4[i];
      }
   }
   // printf("Min : %d\n", min);
   
   return 1;
}

int main(int argc, char const **argv) {
   
   int input_n = atoi(argv[1]);
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
   int no_fn_calls = 12;
   int *arr_fn_calls_nos = (int *) malloc(no_fn_calls * sizeof(int));
   for(int i = 0; i < no_fn_calls; ++i) {
      arr_fn_calls_nos[i] = i;
   }

   struct timeval stop, start;
   gettimeofday(&start, 0);
   sort(arr1, n);
   #pragma omp parallel sections 
   {
      #pragma omp section 
      my_min(arr1, n);
      #pragma omp section 
      my_max(arr1, n);
      #pragma omp section 
      ceilSearch(arr1, 0, input_n, 2147483484);
      #pragma omp section 
      countOccurrences(arr1, input_n, 2147483484);
      #pragma omp section 
      binarySearch(arr1, 0, input_n, 2147483484);
   }
   gettimeofday(&stop, NULL);
   printf("%lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
	
}

