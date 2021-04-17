#include <iostream>
#include <sys/time.h>
#include "prog.hpp"

using namespace std;

int main(int argc, char **argv)
{
	int input_n = atoi(argv[1]);
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

	struct timeval stop, start;
    gettimeofday(&start, NULL);

	my_sort(arr1, n);
	my_min(arr1, n);
	my_max(arr1, n);
	my_sort(arr2, n);
	my_min(arr2, n);
	my_max(arr2, n);
	
	gettimeofday(&stop, NULL);
    printf("%lu\n", ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);
    free(arr1);
    free(arr2);
	return 0;
}