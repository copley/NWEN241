/*
 * q2.c
 *
 *  Created on: 19/05/2015
 *      Author: diego
 */
#include <stdio.h>


int main(void) {
	int m[4][4] = { { 1, 3, 5, 7 }, { 11, 33, 55, 77 }, { 2, 4, 6, 8 }, { 22, 44, 66, 88 } };
	int (*parr)[4] = m;

	printf("**m = %d\n",**m); // 1
	printf("*(*m+2) = %d\n",*(*m+2)); // 5
	printf("*(*(m+1)+1) = %d\n",*(*(m+1)+1)); // *(m+1) is {11, 33, 55, 77}, then *( {11, 33, 55, 77} + 1 ) is the index 1 element in the array so 33
	printf("*(m[1]+2) = %d\n",*(m[1]+2)); // 55
	printf("(*(m+2))[3] = %d\n",(*(m+2))[3]); // 8
	printf("(*(parr+3))[2] = %d\n",(*(parr+3))[2]); // 66

}
