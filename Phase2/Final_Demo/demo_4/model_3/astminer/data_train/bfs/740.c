


struct que
{
	int que[20];
	int f,r,n;
};
void enque(struct que*,int);
int deque(struct que*);
void bfs(int a[100][100],int);
void main()
{
	int a[100][100],start=0,i,j,n;
	printf("Enter size\n");
	scanf("%d",&n);
	printf("enter elements\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	bfs(a,n);
}
void bfs(int a[100][100],int n)
{
	int i,visit[100],start=0,k,j;
	for(i=0;i<n;i++)
	{
		visit[i]=0;
	}
	struct que *q;
	q=(struct que*)malloc(sizeof(struct que));
	q->f=-1;
	q->r=-1;
	q->n=20;
	enque(q,start);
	while(q->f!=q->r)
	{
		k=deque(q);
		if(visit[k]==0)
		{
			visit[k]=1;
			printf("%d",k);
		for(j=0;j<n;j++)
		{
			if(a[k][j]==1 && visit[j]==0)
			{
				enque(q,j);
			}
		}
		}
	}
}
void enque(struct que *q,int start)
{	
	q->r++;
	q->que[q->r]=start;
}
int deque(struct que *q)
{
	q->f++;
	return q->que[q->f];
}





