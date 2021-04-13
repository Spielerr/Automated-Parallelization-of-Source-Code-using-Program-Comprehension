#include "prog.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void my_sort(int* arr, int n)
{
	// sort(arr, arr + n);
	quickSort(arr, 0, n-1);
}

int my_min(int* arr, int n)
{
	// return *min_element(arr, arr+n);
	int min = arr[0];
	for(int i = 1; i<n; i++)
	{
		if(arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

int my_max(int* arr, int n)
{
	// return *max_element(arr, arr+n);
	int max = arr[0];
	for(int i = 1; i<n; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}