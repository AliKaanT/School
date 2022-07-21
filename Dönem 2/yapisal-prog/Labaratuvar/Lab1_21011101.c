#include <stdio.h>
#define MAX_SIZE 100
int main() {

	int i,j ;

	int A[MAX_SIZE],N;
	int counter;

	printf("Dizi boyutunu giriniz : ");
	scanf("%d",&N);

	for(i=0; i<N; i++) {
		printf("%d. eleman : ",i+1);
		scanf("%d",&A[i]);
	}
	printf("-------------------------\n");
	for(i=0;i<N;i++){
		counter=0;
		for(j=0; j<N; j++) {
			if(A[i]==A[j] && j<i){
				counter = (MAX_SIZE+1);	// Ayný sayiyi bir kac defa yazmamasi icin counteri MAX ile esitleyerek bozdum. Boylece bir sayiyi 2 kere print edemez.
			}
			if(A[i]==A[j]) {
				counter++;
			}
		}
		if(counter == A[i]) {
			printf("%d bir sihirli sayidir\n",A[i]);
		}
	}
	return 42;
}
