#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

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

int binarySearch(int arr[], int l, int r, int x,  int fn_call_no)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
        {
			printf("%d: Index : %d\n",fn_call_no, m);
			return 1;
		}
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void sort(int* arr,const int arr_n, int fn_call_no)
{
	for(int i = 0;i < arr_n-1;++i)
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


int my_max(int* a4, int n4, int fn_call_no)
{
	int max = a4[0];
	for(int i = 1; i < n4; ++i)
	{
		if(a4[i]>max)
		{
			max = a4[i];
		}
	}

	printf("%d: Max : %d\n",fn_call_no, max);
	return 1;
}

int my_min(int* a4, int n4, int fn_call_no)
{
	int min = a4[0];
	for(int i = 1; i<n4; ++i)
	{
		if(a4[i]<min)
		{
			min = a4[i];
		}
	}

	printf("%d: Min : %d\n",fn_call_no, min);
	return 1;
}

int countOccurrences(int arr[], int n, int x, int fn_call_no)
{
    int res = 0;
    for (int i=0; i<n; i++)
        if (x == arr[i])
          res++;
	printf("%d: Min Occurence of %d : %d\n",fn_call_no, x, res);
    return 1;
}


int ceilSearch(int arr[], int low, int high, int x, int fn_call_no)
{
     
    int i;
    if(x <= arr[low])
        return low;
     
    for(i = low; i < high; i++)
    {
        if(arr[i] == x)
        return i;
     
        if(arr[i] < x && arr[i+1] >= x)
        return i+1;
    }    
    return -1;
}

int main(int argc, const char** argv)
{

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	int input_n = 30000;
	int *arr1 = (int *)malloc(input_n * sizeof(int));
	int array_size1 = input_n;
	srand(8);
	for(int i = 0; i < array_size1; ++i)
	{    
		arr1[i] = rand();
	}

	int *arr2 = (int *)malloc(input_n * sizeof(int));
	int array_size2 = input_n;
	srand(2);
	for(int i = 0; i < array_size2; ++i)
	{    
		arr2[i] = rand();
	}

	int n = array_size1;

	int no_fn_calls = 12;

	int* arr_fn_calls_nos = (int*)malloc(no_fn_calls*sizeof(int));

	for(int i = 0; i < no_fn_calls; ++i)
	{
		arr_fn_calls_nos[i] = i;
	}


	sort(arr1, n, arr_fn_calls_nos[0]);
	my_min(arr1, n, arr_fn_calls_nos[1]);
	my_max(arr1, n, arr_fn_calls_nos[2]);


}