







int P, N, i = 0, j = 0, weight = 0, var = 0;
int w[1000], v[1000], answ[1000], A[1000][1000];

void print(unsigned char choice)
{
    int i = 1;
    for (; i <= N; i++)
    {
        if (answ[i])
        {
            switch(choice)
            {
                case 1:
                    printf("%d ", i);
                    break;
                case 2:
                    printf("%d ", w[i]);
                    weight += w[i];
                    break;
                case 3:
                    printf("%d ", v[i]);
                    var += v[i];
                    break;
            }
        }
    }
}

