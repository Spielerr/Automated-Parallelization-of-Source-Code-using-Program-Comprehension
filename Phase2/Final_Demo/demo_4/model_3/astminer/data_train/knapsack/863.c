
struct FKS
{
	int obId;
	int profit;
	int weight;
	float pByw;
};
void insertionSort(struct FKS *arr, int num)
{
	int ind1, ind2;
	struct FKS temp;
	for( ind1 = 1 ; ind1 < num ; ind1++ )
	{
		ind2 = ind1 - 1;
		temp = arr[ind1];
		while( ind2 >= 0 && arr[ind2].pByw < temp.pByw )
		{
			arr[ind2+1] = arr[ind2];
			ind2 = ind2 - 1;
		}
		arr[ind2+1] = temp;
	}
}
float fractionalKnapsack( struct FKS *arr, int num, int capacity )
{
	int ind;
	float maxPro = 0.0 ;
	for( ind = 0 ; ind < num ; ind++ )
	{
		if( capacity > 0 && arr[ind].weight < capacity )
		{
			capacity = capacity - arr[ind].weight;
			maxPro = maxPro + arr[ind].profit;
		}
		else 
			break;
	}
	if( capacity > 0 )
		maxPro = maxPro + arr[ind].pByw * capacity ;
	return maxPro;
}
