
// void dispArr(int *arr, int n);
void bubbleSort(int *arr,int n);

// void dispArr(int *arr, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d\t", arr[i]);
//     }
//     printf("\n");
// }

void bubbleSort(int *arr,int n){
    int temp,isSorted=0;
    for(int i=0; i<n-1; i++){
        printf("Pass %d\n",i+1);
        isSorted=1;
        for(int j=0; j<n-1-i; j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                isSorted=0;
            }
            
        }
        if(isSorted)
                return;
    }
}