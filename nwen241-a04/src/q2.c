/*
 * NWEN241-A04_02.c
 *
 *  Created on: 5/05/2015
 *      Author: diego
 */

#include <stdio.h>
#define SIZE 10

void v_exchange(int a[]);
void v_exchangep(int a[]);

int main(void) {
	int i, x[SIZE]; /* x[] has 10 int elements */
	for (i = 0; i < SIZE; i++)
		x[i] = i; /* assign i to x[i] */
	v_exchangep(x); /* call for value exchange */
	for (i = 0; i < SIZE; i++)
		printf("x[%d]=%d, &x[%d]=%x\n", i, x[i], i, &x[i]);
	return 0;
}

void v_exchange(int a[]){
	int x;
	for (int i=0; i<SIZE/2; i++){
		x = a[SIZE-1-i];
		a[SIZE-1-i]=a[i];
		a[i] = x;
	}
}

void v_exchangep(int a[]){

	int * front;
	int * end;
	int i;

	for (i=0; i<SIZE/2; i++){
		front = a+i;
		end = a+SIZE-1-i;
		int front_int = *front;
		*front = *end;
		*end = front_int;
	}
}

