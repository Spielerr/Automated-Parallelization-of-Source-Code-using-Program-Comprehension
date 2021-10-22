

int a[20][20], q[20], visited[20];
int n, i, j, f = 0, r = -1;

void bfs(int v);

void main()
{
    int ver;

    printf("\n Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        q[i] = 0;
        visited[i] = 0;
    }

    printf("\nEnter graph data in matrix form:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    printf("\nEnter the starting vertex: ");
    scanf("%d", &ver);

    bfs(ver);

    printf("\n The node which are reachable are:\n");
    for (i = 1; i <= n; i++)
    {
        if (visited[i])
        {
            printf("%d\t", i);
        }
        else
        {
            printf("\n Bfs is not possible");
        }
    }
}
void bfs(int v)
{
    for (i = 1; i <= n; i++)
    {
        if (a[v][i] && !visited[i])
        {
            q[++r] = i;
        }
    }
    if (f <= r)
    {
        visited[q[f]] = 1;
        bfs(q[f++]);
    }
}