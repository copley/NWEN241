#include <stdio.h>

void bitwise_swap(int *x, int *y){
	if (*x!=*y){
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

int main(void){
	int a = 543;
	int b = 267;
	printf("A %d B %d\n",a,b);
	bitwise_swap(&a,&8b);
	printf("A %d B %d\n",a,b);
}