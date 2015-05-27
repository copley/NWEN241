/*
 ============================================================================
 Author      : Diego Trazzi
 Description :a program that prints * ** ***.
 int row // row counter  and    int col // column counter
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int row;
	int col;

	for (row = 1; row < 5; row++) {
		for (col = 0; col < row; col++) {
			printf("*");
		}
		printf("\n");
	}
	return(0);
}
