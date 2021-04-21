#include <iostream>
#include <algorithm>
#include "prog.hpp"
using namespace std;

void my_sort(int* arr, int n)
{
	sort(arr, arr + n);
}

int min(int* arr, int n)
{
	return arr[0];
}

int max(int* arr, int n)
{
	return arr[n-1];
}

	
