




int list[MAX_SIZE];
int n;

void selection_sort(int list[], int n){
    int i, j, least, temp;
    for(i=0; i<n-1; i++){
        least = i;
        for(j=i+1; j<n; j++) 
            if(list[j]<list[least]) least = j;
        SWAP(list[i], list[least], temp);
    }
}

void main(){
    int i;
    n= MAX_SIZE;
    for(i=0; i<n; i++) 
        list[i] = rand()%n; 
    selection_sort(list, n); 

    for(i=0; i<n; i++)   
        printf("%d\n", list[i]);
}