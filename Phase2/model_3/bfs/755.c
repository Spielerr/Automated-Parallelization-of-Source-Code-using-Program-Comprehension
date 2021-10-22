


void bfs(int m[max][max],int v,int source)
{
	int queue[20];
	int front=0;
	int rear=0;
	int u;
	int visited[max]={0};
	queue[rear]=source;
	visited[source]=1;
	while(front<=rear)
	{
		u=queue[front];
		printf("%d\n",u);
		front+=1;
		for(int i=0;i<v;i++)
		{
			if(m[u][i]==1 && visited[i]==0)
			{
				visited[i]=1;
				rear+=1;
				queue[rear]=i;
			}
		}
	}

}