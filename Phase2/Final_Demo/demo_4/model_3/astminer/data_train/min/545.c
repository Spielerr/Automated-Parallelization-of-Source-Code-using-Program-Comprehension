


void maxMin(int *arr,int size){
int max=arr[0],min=arr[0];

for (int i=0;i<size;i++){
	if (*(arr+i)>max){
		max=*(arr+i);
	}

	if (*(arr+i)<min){
		min=*(arr+i);
	}
}


printf("\n Maximum %d, Minimum %d \n",max,min);
}

