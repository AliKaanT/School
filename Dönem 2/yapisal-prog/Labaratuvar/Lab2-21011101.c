#include <stdio.h>
#define MAX 15

int main() {


	int N,M;
	int A[MAX][MAX];
	int x=0,y=0; //baslangic noktasi
	int i,j;

	int flag = 0;
	int control=0;

	do {
		printf("N degeri giriniz : ");
		scanf("%d",&N);
	}	while(N>MAX || N<=0);

	do {
		printf("M degeri giriniz : ");
		scanf("%d",&M);
	}	while(M>MAX || M<=0);

	printf("\nElemanlari giriniz!! (0 veya 1)\n\n");

	for(i=0; i<N; i++) {
		for(j=0; j<M; j++) {
			do {
				printf("eleman (%d,%d) : ",i+1,j+1);
				scanf("%d",&A[i][j]);
			} while(A[i][j]!=1 && A[i][j]!=0);
		}
		printf("\n");
	}

	for(i=0; i<N; i++) {
		for(j=0; j<M; j++) {
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\n");
	
	while(flag==0 && x<N && y<M) {
		if(A[x+1][y]==1) {
			x=x+1;
			printf("2 ");
			control=1;
		} else if(A[x][y+1]==1) {
			y=y+1;
			printf("1 ");
			control=1;
		} else {
			flag = 1;
		}
	}
	printf("%d",m);
	
	if(control==0){
		printf("Rota yok!!");
	}

	return 0;
}
