#include <stdio.h>

int main(void){
	int n,i;
	int m = 1 << 31;
	printf("Insert a number to convert in binary ");
	scanf("%d",&n);

	for(i=0;i<32;i++){
		if (i%8==0) printf(" ");
		printf("%d",((n&m)!=0?1:0));
		m = m >> 1;
	}
	printf("\n");
}