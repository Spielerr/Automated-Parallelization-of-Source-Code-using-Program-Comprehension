


void selectionsort(double* x, int n){
    
    int i;
    int j;
    for (i=0;i<n;i++)
    {
        for (j=i+1; j < n ; j++)
        {
            double elem_1 = x[i];
            double elem_2 = x[j];
            
            if (elem_2 < elem_1)
            {
                x[i] = elem_2;
                x[j] = elem_1;
            }
        }
    }


}
