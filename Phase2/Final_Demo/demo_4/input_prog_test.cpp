#include <stdio.h>
#include <stdlib.h>

double mean(const int* a1, int n1)
{
	double mean = 0;
	for(int i = 0;i < n1;++i)
	{
		mean += a1[i];
	}
	mean /= n1;
	return mean;
}



void my_sort(int* arr,const int arr_n)
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


int my_max(int* a4, int n4)
{
	int max = a4[0];
	for(int i = 1; i < n4; ++i)
	{
		if(a4[i]>max)
		{
			max = a4[i];
		}
	}

	return 1;
}

int my_min(int* a4, int n4)
{
	int min = a4[0];
	for(int i = 1; i<n4; ++i)
	{
		if(a4[i]<min)
		{
			min = a4[i];
		}
	}
	return 1;
}


int binarySearch(int arr[], int l, int r, int x)
{
	int l_ = l;
	int r_ = r;
    while (l_ <= r_) {
        int m = l_ + (r_ - l_) / 2;
        if (arr[m] == x)
        {
			// printf("%d: Index : %d\n",fn_call_no, m);
			return 1;
		}
        if (arr[m] < x)
            l_ = m + 1;
        else
            r_ = m - 1;
    }
	// printf("%d: Index : %d\n",fn_call_no, -1);
    return -1;
}


int countOccurrences(int arr[], int n, int x)
{
    int res = 0;
    for (int i=0; i<n; i++)
        if (x == arr[i])
          res++;
	// printf("%d: Count of %d : %d\n",fn_call_no, x, res);
    return 1;
}


int ceilSearch(int arr[], int low, int high, int x)
{
     
    int i;
    if(x <= arr[low])
		{
			// printf("%d:	Ceil of %d : %d\n",fn_call_no, x, arr[low]);
        	return low;
		}
     
    for(i = low; i < high; i++)
    {
        if(arr[i] == x)
		{
			// printf("%d: Ceil of %d : %d\n",fn_call_no, x, arr[i]);
       		return i;
		}
     
        if(arr[i] < x && arr[i+1] >= x)
		{
			// printf("%d: Ceil of %d : %d\n",fn_call_no, x, arr[i+1]);
        	return i+1;
		}
    }    
	// printf("%d: Ceil of %d : %d\n",fn_call_no, x, -1);
    return -1;
}


int main(int argc, const char** argv)
{
	int n = 1000;


	int *arr1 = (int*)malloc( sizeof(int) * n );
	int *arr2 = (int*)malloc( sizeof(int) * n );

	srand(8);

	for(int i = 0; i < n; ++i)
	{    
		arr1[i] = rand();
		arr2[i] = rand();
	}

	my_sort(arr1, n);
	int x1 = 8*2;
	
	if((x1-4)%4 == 0)
	{
		ceilSearch(arr1, 0, n, 2147483484);
	}
	else
	{
	    countOccurrences(arr1, n, 2147483484);
	}
	
	binarySearch(arr1, 0, n, 2147483484);

	int f1 = 10;

	my_sort(arr2, n);
	
	for(int i=0; i<2; ++i)
	{
		ceilSearch(arr2, 0, n, 2147470276);
	}
	
	countOccurrences(arr2, n, 2147470276);
	binarySearch(arr2, 0, n, 2147470276);
}
