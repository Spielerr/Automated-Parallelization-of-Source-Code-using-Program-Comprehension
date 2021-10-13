int binarySearch(int arr[], int l, int r, int x,  int fn_call_no)
{
	int l_ = l;
	int r_ = r;
    while (l_ <= r_) {
        int m = l_ + (r_ - l_) / 2;
        if (arr[m] == x)
        {
			printf("%d: Index : %d\n",fn_call_no, m);
			return m;
		}
        if (arr[m] < x)
            l_ = m + 1;
        else
            r_ = m - 1;
    }
	printf("%d: Index : %d\n",fn_call_no, -1);
    return -1;
}
