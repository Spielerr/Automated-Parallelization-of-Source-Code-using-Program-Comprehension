




int list[MAX_SIZE];
int n;

void selectionSort(int list[], int n){
    int i, j, least, temp;
    for(i=0; i<n-1; i++){
        least = i;
        for(j=i+1; j<n; j++) 
            if(list[j]<list[least]) least = j;
        SWAP(list[i], list[least], temp);
    }
}

