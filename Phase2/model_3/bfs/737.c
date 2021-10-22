

int G[20][20],q[20],visited[20],front = -1, rear = -1 ,E,V;
void bfs(int v)
{
    visited[v] = 1;
    q[++rear]=v;
    front=0;
    while(front<=rear)
    {
        int n=q[front++];
        printf("%d ",n );

        for(int i=0;i<V;i++)
        {
            if(G[n][i]==1 && visited[i]==0)
            {   
                visited[i]=1;
                q[++rear]=i;
            }
        }

    }
 }