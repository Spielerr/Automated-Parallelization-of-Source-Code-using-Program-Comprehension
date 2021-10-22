
void main()
{
int n,i,j,temp,selection[10];
clrscr();
printf("\nEnter total no. of elements: ");
scanf("%d",&n);
printf("\nEnter elements: ");
for(i=0;i<n;++i){
	scanf("%d",&selection[i]);
}

for(i=0;i<n-1;++i)
{
	for(j=i+1;j<n;++j)
	{
	if(selection[i]>selection[j])
	{
	temp = selection[j];
	selection[j] = selection[i];
	selection[i] = temp;
	}
	}
}
printf("\nValue of selection sort: ");
for(i=0;i<n;++i)
	printf("%d ",selection[i]);

getch();
}
