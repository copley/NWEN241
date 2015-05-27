/*
 * q7.c
 *  A function swap_ptr which swaps the values between ptrp and ptrq
 *  Created on: 20/05/2015
 *      Author: diego
 */

int swap_ptr (int *, int *);

int main(void){
	int a = 3;
	int b = 4;
	printf("Before swap a: %d b: %d\n",a, b);
	swap_ptr(&a, &b);
}

int swap_ptr( int *ptrp, int *ptrq){
	int *tmp = ptrp;
	ptrp = ptrq;
	ptrq = tmp;
	printf("After swap a: %d b: %d\n",*ptrp, *ptrq);
	return 0;
}

