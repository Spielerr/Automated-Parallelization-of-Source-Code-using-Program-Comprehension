

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



