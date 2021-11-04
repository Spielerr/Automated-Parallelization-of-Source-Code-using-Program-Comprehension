


struct array{
    int *A;
    int size;
};

void selectionSort(int B[],int size){
    
    for(int i=0;i<size;i++){
    int k,j;
    k=i;    
    int x=B[i];
    for(int j=i;j<size;j++){
            if(B[j]<x){
                x=B[j];
                k=j;
            }
        }
        int temp=B[i];
        B[i]=B[k];
        B[k]=temp;
    
    }

}

