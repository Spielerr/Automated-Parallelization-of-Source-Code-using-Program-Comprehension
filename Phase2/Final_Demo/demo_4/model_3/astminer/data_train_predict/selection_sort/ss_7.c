

void selectionSort(int *A,int n){
    int temp;
    for(int i=0;i<n-1;i++){
        int indexOfMin=i;
        for(int j=i+1;j<n;j++){
            if(A[j]<A[indexOfMin]){
                indexOfMin=j;
            }
            temp=A[i];
            A[i]=A[indexOfMin];
            A[indexOfMin]=temp;
        }
    }
}
