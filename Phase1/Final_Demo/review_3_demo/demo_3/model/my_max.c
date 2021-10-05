int my_max(int* a, int n, int fn_call_no)
{
	int max = a[n-1];

	printf("%d: Max : %d\n",fn_call_no, max);
	return max;
}
