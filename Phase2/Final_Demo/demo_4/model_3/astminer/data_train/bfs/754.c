



struct arra{
	int b[50];
	int f;
	int r;
};
void enque(int ele,struct arra *p){
	p->f++;
	p->b[p->f]=ele;
}
int deque(struct arra *p){
	p->r++;
	return p->b[p->r];
}
int isempty(struct arra *p){
	if(p->f<=p->r){
		return 1;
	}
	else{
		return 0;
	}
}
void print(int visit[],int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d ,",visit[i]);
	}
}
