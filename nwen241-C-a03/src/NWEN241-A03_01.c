/*
 ============================================================================
 Author      : Diego Trazzi
 Description : A program that finds the smallest of several integers entered by user
 ============================================================================

 int number; number of integers to be entered  int value; value input by user
 int smallest; smallest number
 int i; counter

 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {

	int number;
	int smallest = INT_MAX;
	int value;

	printf("Number of integers to be compared: ");
	scanf("%d", &number); // & gets the memory address

	for (int i = 0; i < number; i++) {
		printf("Please enter a value: ");
		scanf("%d", &value);
		if (value < smallest) {
			smallest = value;
		}
	}

	printf("Smallest number you entered is: %d\n", smallest);

	return(0);

}
