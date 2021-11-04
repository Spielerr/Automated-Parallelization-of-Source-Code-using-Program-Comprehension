

void swap(int *m,int *n)
{
	int temp;
	temp=*m;
	*m=*n;
	*n=temp;
}
void main()
{
	int n,price[100],weights[100],i,j;
	printf("enter size\n");
	scanf("%d",&n);
	printf("enter weight and price");
	for(i=0;i<n;i++)
	{
		scanf("%d",&weights[i]);
		scanf("%d",&price[i]);
	
	}
	int ratio[100],value=0;
	int capacity,total=0,k;
	printf("enter capacity of knapsack\n");
	scanf("%d",&capacity);
	
	for (j=0;j<n;j++)
	{
		ratio[j]=price[j]/weights[j];
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(ratio[j]< ratio[j+1])
			{
				swap(&ratio[j],&ratio[j+1]);
				swap(&weights[j],&weights[j+1]);
				swap(&price[j],&price[j+1]);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(total+weights[i] <= capacity)
		{
			total+=weights[i];
			value+=price[i];
		}
		else
		break;
	}
	if(total != capacity)
	{
		k=capacity-weights[i];
		value=value+k*ratio[i];
		total+=k;
	}
	printf("%d",value);
	printf("%d",total);
	
}
