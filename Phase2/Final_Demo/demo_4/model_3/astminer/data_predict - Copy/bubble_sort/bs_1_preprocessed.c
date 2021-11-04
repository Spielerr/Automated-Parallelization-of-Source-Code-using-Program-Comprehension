

int nums[] = { 5, 23, -6, 13, 100, 2, 19 };

void bubbleSort(int a[], int len)
{
  int swapped;

  do {
    swapped = 0;

    for(int i = 1; i <= len-1; i++) {
      if (a[i-1] > a[i]) {
 int t = a[i];
 a[i] = a[i-1];
 a[i-1] = t;
 swapped = 1;
      }
    }
  } while (swapped);
}
