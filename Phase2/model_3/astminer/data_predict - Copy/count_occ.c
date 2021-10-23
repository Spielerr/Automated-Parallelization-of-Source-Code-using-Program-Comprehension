int countOccurrences(int arr[], int n, int x, int fn_call_no)
{
    int res = 0;
    for (int i=0; i<n; i++)
        if (x == arr[i])
          res++;
	printf("%d: Count of %d : %d\n",fn_call_no, x, res);
    return 1;
}
