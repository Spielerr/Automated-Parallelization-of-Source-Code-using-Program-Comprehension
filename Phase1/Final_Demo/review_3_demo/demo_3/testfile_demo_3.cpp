#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <algorithm>
#include <parallel/numeric>
double mean(int const *a1, int n1, int fn_call_no) {
   double* s;
   __gnu_parallel::partial_sum( a1, a1 + n1, s );
   return *s/n1;
}

#include <parallel/algorithm>
void sort(int *arr, int const arr_n, int fn_call_no) {
   __gnu_parallel::sort(arr, arr + arr_n );
}

int my_max(int *a4, int n4, int fn_call_no) {
   int max = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] > max) {
         max = a4[i];
      }
   }
   printf("%d: Max : %d\n", fn_call_no, max);
   
   return 1;
}

int my_min(int *a4, int n4, int fn_call_no) {
   int min = a4[0];
   for(int i = 1; i < n4; ++i) {
      if(a4[i] < min) {
         min = a4[i];
      }
   }
   printf("%d: Min : %d\n", fn_call_no, min);
   
   return 1;
}

int binarySearch(int arr[], int l, int r, int x, int fn_call_no) {
   int l_ = l;
   int r_ = r;
   while(l_ <= r_) {
      int m = l_ + (r_ - l_) / 2;
      if(arr[m] == x) {
         printf("%d: Index : %d\n", fn_call_no, m);
         
         return 1;
      }
      if(arr[m] < x) l_ = m + 1;
      else r_ = m - 1;
   }
   printf("%d: Index : %d\n", fn_call_no, -1);
   
   return -1;
}

int countOccurrences(int arr[], int n, int x, int fn_call_no) {
   int res = 0;
   for(int i = 0; i < n; i++) if(x == arr[i]) res++;
   printf("%d: Count of %d : %d\n", fn_call_no, x, res);
   
   return 1;
}

int ceilSearch(int arr[], int low, int high, int x, int fn_call_no) {
   int i;
   if(x <= arr[low]) {
      printf("%d:\tCeil of %d : %d\n", fn_call_no, x, arr[low]);
      
      return low;
   }
   for(i = low; i < high; i++) {
      if(arr[i] == x) {
         printf("%d: Ceil of %d : %d\n", fn_call_no, x, arr[i]);
         
         return i;
      }
      if(arr[i] < x && arr[i + 1] >= x) {
         printf("%d: Ceil of %d : %d\n", fn_call_no, x, arr[i + 1]);
         
         return i + 1;
      }
   }
   printf("%d: Ceil of %d : %d\n", fn_call_no, x, -1);
   
   return -1;
}
