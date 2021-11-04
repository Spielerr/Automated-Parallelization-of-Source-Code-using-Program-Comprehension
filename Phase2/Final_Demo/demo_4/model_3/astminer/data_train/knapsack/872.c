
int max(int,int);
int m,i,j,n,p[10],w[10],v[10][10],x[10],op_soln;
int knapsack();

void main()
{
    printf("ENTER THE NUMBER OF OBJECTS\n");
    scanf("%d",&n);
    
    printf("Enter the weights of %d objects\n",n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&w[i]);
    }
    
    printf("Enter the profit of %d objects\n",n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
    }
    
    printf("Enter the capacity of knapsack\n");
    scanf("%d",&m);
    
    op_soln=knapsack(n,w,m,v,p);
    
    printf("The output is\n");
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=m;j++)
        {
            printf("%d\t",v[i][j]);
        }
        printf("\n");
    }
    
    printf("Optimal solution=%d\n",op_soln);
    objected_selected();
    
    }
    int max(int a,int b)
    {
        return(a>b?a:b);
    }

    int knapsack()
    {
        int i,j;
        for(i=0;i<=n;i++)
        {
            for(j=0;j<=m;j++)
            {
                if(i==0||j==0)
                v[i][j]=0;
                else
                if(w[i]>j)
                v[i][j]=v[i-1][j];
                else
                v[i][j]=max(v[i-1][j],v[i-1][j-w[i]]+ p[i]);
            }
        }
        return v[i-1][j-1];
    }

    int objected_selected()
    {
        i=n;
        j=m;
        while(i!=0&&j!=0)
        {
            if(v[i][j]!=v[i-1][j])
            {
                x[i]=1;
                j=j-w[i];
            }
            i--;
        }
        
        printf("Objects selected are : \n");
        for(i=1;i<=n;i++)
        {
            if(x[i]==1)
            printf("%d\n",i);
        }
    }
