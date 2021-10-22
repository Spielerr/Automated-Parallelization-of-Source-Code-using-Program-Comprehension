int f(int a)
{
    if(a==1 || a==0)
    {
        return 1;
    }
    else return a*f(a-1);
}