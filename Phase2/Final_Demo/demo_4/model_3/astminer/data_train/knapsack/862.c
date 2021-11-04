

void swap(float *m,float *n)
{
	float temp;
	temp=*m;
	*m=*n;
	*n=temp;
}
void main()
{
	int n,i,j;
	float price[100],weight[100];
	printf("enter no.of items in kanpsack\n");
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{	
		printf("enter weight(%d) price(%d):",i,i);
		scanf("%f",&weight[i]);
		scanf("%f",&price[i]);
	}
	float ratio[100];
	float profit=0;
	int capacity,total_weight=0,remain;
	printf("enter capacity of knapsack\n");
	scanf("%d",&capacity);
	
	for (j=0;j<n;j++)
	{
		ratio[j]=price[j]/weight[j];
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(ratio[j] < ratio[j+1])
			{
				swap(&ratio[j],&ratio[j+1]);
				swap(&weight[j],&weight[j+1]);
				swap(&price[j],&price[j+1]);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(total_weight+weight[i] <= capacity)
		{
			total_weight+=weight[i];
			profit+=price[i];
			printf("%f\n",weight[i]);
		}
		else
		{
			remain=capacity-total_weight;
			profit+= remain*ratio[i];
			printf("%d\n",remain);
			break;
		}
	}
	printf("profit=(%f)\n",profit);

	printf("\n");
	
}
