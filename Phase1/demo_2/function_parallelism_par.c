#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
void sort(int* arr, int arr_n)
{
	for(int i = 0;i<arr_n-1;++i)
	{
		int min = i;
		for(int j = i+1;j<arr_n;++j)
		{
			if(arr[j]<arr[min])
			{
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

double mean(int* a1, int n1)
{
	double mean = 0;
	for(int i = 0;i<n1;++i)
	{
		mean += a1[i];
	}
	mean /= n1;
	return mean;
}

// int median(int* a2, int n2)
// {
// 	sort(a2,n2);

// 	if (n2 % 2 != 0)
// 	{
// 		return a2[n2 / 2];
// 	}
		
// 	return (a2[(n2 - 1) / 2] + a2[n2 / 2]) / 2.0;

// }

// int search(int *a3, int n3, int key)
// {
// 	for(int i = 0;i<n3;++i)
// 	{
// 		if(a3[i]==key)
// 		{
// 			return i;
// 		}
// 	}
// 	return -1;
// }

int max(int *a4, int n4)
{
	int max = a4[0];
	for(int i = 1; i<n4; ++i)
	{
		if(a4[i]>max)
		{
			max = a4[i];
		}
	}

	return max;
}

int min(int *a4, int n4)
{
	int min = a4[0];
	for(int i = 1; i<n4; ++i)
	{
		if(a4[i]<min)
		{
			min = a4[i];
		}
	}

	return min;
}



int main()
{
    int *array = (int *)malloc(50000 * sizeof(int));
    int array_size = 50000;
    srand(8);
    for(int i = 0; i < array_size; ++i)
    {    
        array[i] = rand();
    }
	// double m1 = mean(array, array_size);
	// int m2 = median(array, array_size);
	sort(array, array_size);
	int m3 = max(array, array_size);
	int m4 = min(array,array_size);
	// int k = search(array,array_size,4);

	return 0;
}