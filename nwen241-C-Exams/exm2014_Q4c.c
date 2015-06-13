#include <stdio.h>

int main(void){
	unsigned int n, i;
	scanf("%d",&n);
	printf("Decimal number : %d\n",n);
	unsigned mask = 1 << 31;

	for (i=0;i<32;i++){
		if (i%8==0) printf(" ");
		printf("%d",(n&mask)==0?0:1);
		mask >>= 1;
	}
	printf("\n");

}