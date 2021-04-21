#include <iostream>
#include <algorithm>
using namespace std;

void my_sort(int* arr, int n)
{
	sort(arr, arr + n);
}

int min(int* arr, int n)
{
	// cout << arr[0] << "\n";
	return arr[0];
}

int max(int* arr, int n)
{
	// cout << arr[n-1] << "\n";
	return arr[n-1];
}