
int max(int a, int b) { return (a > b)? a : b; }
int knapSack(int W, int wt[], int val[], int n)
{
   int i, j,w;
   int K[n+1][W+1];
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
	
	printf("\nThe knapsack matrix is: \n");
	for(i=0;i<=n;i++)
	{
		for( j=0;j<=W;j++)
		{
			printf("%d\t",K[i][j]);
		}
		printf("\n");
	}
	
	i=n;
	w=W;
	printf("\nobjects\tweights\tprofits\n");
	while(w!=0 && i!=0){
		if(K[i][w]!=K[i-1][w]){
			printf("%d\t%d\t%d\n",i,wt[i-1],val[i-1]);
			w=w-wt[i-1];
		}
		i--;
	}
   
   return K[n][W];
}
