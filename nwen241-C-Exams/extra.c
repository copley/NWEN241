#include <stdio.h>

int swap_ptr (int *, int *);

int main(void){
	int a = 3;
	int b = 4;
	printf("Before swap a: %d b: %d\n",a, b);
	swap_ptr(&a, &b);
	printf("After swap a: %d b: %d\n",a, b);
}

int swap_ptr(int *ptrp, int *ptrq){
	int tmp = *ptrp;
	*ptrp = *ptrq;
	*ptrq = tmp;
	printf("After swap inside function a: %d b: %d\n",*ptrp, *ptrq);
	return 0;
}