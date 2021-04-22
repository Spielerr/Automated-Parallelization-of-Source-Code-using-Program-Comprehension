

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
	sort(arr2, n, arr_fn_calls_nos[3]);
	my_min(arr2, n, arr_fn_calls_nos[4]);
	my_max(arr2, n, arr_fn_calls_nos[5]);

	sort(arr1, n, arr_fn_calls_nos[6]);
	my_min(arr1, n, arr_fn_calls_nos[7]);
	my_max(arr1, n, arr_fn_calls_nos[8]);
	sort(arr2, n, arr_fn_calls_nos[9]);
	my_min(arr2, n, arr_fn_calls_nos[10]);
	my_max(arr2, n, arr_fn_calls_nos[11]);

	
	gettimeofday(&stop, NULL);
	printf("Time Taken : %lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

}

					
					
				
			
			
			
			

		
		
	
