/*
 ============================================================================
 Author      : Diego Trazzi
 Description : a program that counts and prints the number of each different letter grade user entered
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
	char grade; /* current grade. You can also use char grade. You may use either getchar or scanf to handle the input. */
	int aCount = 0; /* total a grades */
	int bCount = 0; /* total b grades */
	int cCount = 0; /* total c grades */
	int dCount = 0; /* total d grades */
	int eCount = 0; /* total e grades */

	printf("Enter grade (A-F,a-f). Enter x to terminate.\n");

	while (grade != 'X') {
		grade = toupper(getchar());
		switch (grade) {
		case ('A'):
			aCount++;
			break;
		case ('B'):
			bCount++;
			break;
		case ('C'):
			cCount++;
			break;
		case ('D'):
			dCount++;
			break;
		case ('E'):
			eCount++;
			break;

		}
	}

	printf("Total number of A: %d\n", aCount);
	printf("Total number of B: %d\n", bCount);
	printf("Total number of C: %d\n", cCount);
	printf("Total number of D: %d\n", dCount);
	printf("Total number of E: %d\n", eCount);

	return (0);
}


