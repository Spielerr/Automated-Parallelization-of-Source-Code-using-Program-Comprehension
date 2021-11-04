
int maxwv(int items , int weight[], int value[] , int capacity , int index)
{
    int vin,vout;
    if(index==items || capacity == 0)
    {
    return 0;
    }
    if(weight[index]<=capacity)
    {
        vin = maxwv(items , weight , value , capacity - weight[index] ,index+1)+value[index];
        vout = maxwv(items , weight , value , capacity, index+1);
        if(vin>vout)
        return vin;
        else
        return vout;
    }
    else
    {
        vout = maxwv(items , weight , value , capacity , index+1);
        return vout;
    }
}
