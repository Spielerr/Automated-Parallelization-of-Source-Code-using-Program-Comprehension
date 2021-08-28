#include <iostream>
#include <algorithm>
using namespace std;

void my_sort(int* arr, int n)
{
	sort(arr, arr + n);
}

void min(int* arr, int n)
{
	cout << arr[0] << "\n";
	// return arr[0];
}

void max(int* arr, int n)
{
	cout << arr[n-1] << "\n";
	// return arr[n-1];
}

int main()
{
	int arr1[]{2, 1, 3, 6, 5};
	int arr1[]{2, 0, 3, 6, 5};
	int n = sizeof(arr) / sizeof(arr[0]);

	my_sort(arr1, n);
	int min1 = min(arr1, n);
	int max1 = max(arr1, n);

	my_sort(arr2, n);
	int min2 = min(arr2, n);
	int max2 = max(arr2, n);

	return 0;
}