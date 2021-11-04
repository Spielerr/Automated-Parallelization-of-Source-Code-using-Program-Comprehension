int ceilSearch(int arr[], int low, int high, int x, int fn_call_no)
{
     
    int i;
    if(x <= arr[low])
		{
			printf("%d:	Ceil of %d : %d\n",fn_call_no, x, arr[low]);
        	return low;
		}
     
    for(i = low; i < high; i++)
    {
        if(arr[i] == x)
		{
			printf("%d: Ceil of %d : %d\n",fn_call_no, x, arr[i]);
       		return i;
		}
     
        if(arr[i] < x && arr[i+1] >= x)
		{
			printf("%d: Ceil of %d : %d\n",fn_call_no, x, arr[i+1]);
        	return i+1;
		}
    }    
	printf("%d: Ceil of %d : %d\n",fn_call_no, x, -1);
    return -1;
}
