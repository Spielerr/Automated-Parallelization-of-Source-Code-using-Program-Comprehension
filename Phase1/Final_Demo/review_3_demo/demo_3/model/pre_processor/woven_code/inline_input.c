#include <stdio.h>
void sort(int array[], int size) {
   for(int step = 0; step < size - 1; ++step) {
      for(int i = 0; i < size - step - 1; ++i) {
         if(array[i] > array[i + 1]) {
            int temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
         }
      }
   }
}

int main() {
   int arr[5] = {10, 40, 20, 30, 50};
   int n = 5;
   for(int i = 0; i < n; ++i) {
      printf("%d\t", arr[i]);
   }
   printf("\n");
   sort(arr, n);
   for(int i = 0; i < n; ++i) {
      printf("%d\t", arr[i]);
   }
   printf("\n");
}
