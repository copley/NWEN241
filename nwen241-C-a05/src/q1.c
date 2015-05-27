/*
 * q1.c
 *
 *  Created on: 19/05/2015
 *      Author: diego
 */
#include <stdio.h>

int main(void){
	int a[3] = {11, 22, 33};
	int *pa = a;

	printf("*a = %d\n", *a);
	printf("*(a+2) = %d\n", *(a+2));
	printf("*pa = %d\n", *pa);
	printf("pa[1] = %d\n", pa[1]);

	return 0;
}
