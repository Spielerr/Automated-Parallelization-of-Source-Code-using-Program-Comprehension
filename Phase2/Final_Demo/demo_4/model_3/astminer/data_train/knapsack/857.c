


int Knapsack(int *w,int *v,int n,int B)
{
	int i,temp;
	int maxVal=0,maxSeq=0;
	int totalWeight=0,totalValue=0;
	int opcount=0;
	int index=0;
	for(i=1;i<pow(2,n);i++)
	{
		totalWeight=0;
		totalValue=0;
		for(int j=0;j<=n;j++)
		{
			if(i & (1<<j))
			{
				totalWeight=totalWeight+w[j];
				totalValue=totalValue+v[j];
			}
		}
		if(totalWeight<=B && totalValue>maxVal)
		{
			
			maxVal=totalValue;
			printf("%d ",maxVal);
			maxSeq=i;
		}
	}
	
	return maxSeq;
}
