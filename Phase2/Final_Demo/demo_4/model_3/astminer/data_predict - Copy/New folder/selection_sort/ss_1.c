

void selectionSort(){
	int i,j,ar[20],n,min,t;
	printf("Enter array limit:");
	scanf("%d",&n);
	printf("Enter elements:\n");
	for(i=0;i<n;i++){
		scanf("%d",&ar[i]);
	}
	for(i=0;i<n-1;i++){
		min=i;
		for(j=i+1;j<n;j++){
			if(ar[min]>ar[j]){
				min=j;
			}
		}
		t=ar[i];
		ar[i]=ar[min];
		ar[min]=t;
	}
	printf("Sorted array:\n");
	for(i=0;i<n;i++){
		printf("%d ",ar[i]);
	}
	printf("\n");
}
