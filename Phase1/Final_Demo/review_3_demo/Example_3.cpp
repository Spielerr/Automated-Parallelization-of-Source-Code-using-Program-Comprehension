#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <algorithm>
double mean(const int* a1, int n1, int fn_call_no)
{
	double mean = 0;
	for(int i = 0;i < n1;++i)
	{
		mean += a1[i];
	}
	mean /= n1;
	return mean;
}



void sort(int* arr,const int arr_n, int fn_call_no)
{
	for(int i = 0; i < arr_n-1; ++i)
	{
		int min = i;
		for(int j = i+1;j < arr_n;++j)
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}


int my_max(int* a, int n, int fn_call_no)
{
	int max = a[n-1];

	printf("%d: Max : %d\n",fn_call_no, max);
	return max;
}

int my_min(int* a, int n, int fn_call_no)
{
	int min = a[0];

	printf("%d: Min : %d\n",fn_call_no, min);
	return min;
}


int binarySearch(int arr[], int l, int r, int x,  int fn_call_no)
{
	int l_ = l;
	int r_ = r;
    while (l_ <= r_) {
        int m = l_ + (r_ - l_) / 2;
        if (arr[m] == x)
        {
			printf("%d: Index : %d\n",fn_call_no, m);
			return m;
		}
        if (arr[m] < x)
            l_ = m + 1;
        else
            r_ = m - 1;
    }
	printf("%d: Index : %d\n",fn_call_no, -1);
    return -1;
}


int countOccurrences(int arr[], int n, int x, int fn_call_no)
{
    int res = 0;
    for (int i=0; i<n; i++)
        if (x == arr[i])
          res++;
	printf("%d: Count of %d : %d\n",fn_call_no, x, res);
    return 1;
}


int ceilSearch(int arr[], int low, int high, int x, int fn_call_no)
{
     
    int i;
    if(x <= arr[low])
		{
			printf("%d:	Ceil of %d : %d\n",fn_call_no, x, arr[low]);
        	return low;
		}
     
    for(i = low; i < high; i++)
    {
        if(arr[i] == x)
		{
			printf("%d: Ceil of %d : %d\n",fn_call_no, x, arr[i]);
       		return i;
		}
     
        if(arr[i] < x && arr[i+1] >= x)
		{
			printf("%d: Ceil of %d : %d\n",fn_call_no, x, arr[i+1]);
        	return i+1;
		}
    }    
	printf("%d: Ceil of %d : %d\n",fn_call_no, x, -1);
    return -1;
}


int main(int argc, const char** argv)
{

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	int input_n = 50000;
	int no_fn_calls = 24;
	int array_size1 = input_n;
	int n = array_size1;

	int* arr_fn_calls_nos = (int*) malloc( no_fn_calls * sizeof(int) );

	for(int i = 0; i < no_fn_calls; ++i)
	{
		arr_fn_calls_nos[i] = i;
	}

	int *arr1 = (int*)malloc( sizeof(int) * n );
	int *arr2 = (int*)malloc( sizeof(int) * n );

	srand(8);

	for(int i = 0; i < n; ++i)
	{    
		arr1[i] = rand();
		arr2[i] = rand();
	}

	sort(arr1, n, arr_fn_calls_nos[0]);
    my_max(arr1, n, arr_fn_calls_nos[1]);
    my_min(arr1, n, arr_fn_calls_nos[2]);
    binarySearch(arr1, 0, n, 2147335086, arr_fn_calls_nos[3]);


	gettimeofday(&stop, NULL);
	printf("Time Taken : %lu ms\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

}
