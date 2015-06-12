#include <stdio.h>

void bitwise_swap(int*, int*);

void bitwise_swap(int* a, int* b){
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int main(void){
	int a = 10;
	int b = 3;
	printf("%d %d\n",a,b);
	bitwise_swap(&a,&b);
	printf("%d %d\n",a,b);
}