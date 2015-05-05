#include <stdio.h>
/*
 * NWEN241-A04_04.c
 *
 *  Created on: 5/05/2015
 *      Author: diego
 */

int stringlen(const char *s); /* prototype */

int main(void) {
	char string[80]; /* create char array */
	printf("Enter a string: ");
	scanf("%[^\n]", string);
	printf("%d\n", stringlen(string));
	return 0;
}

int stringlen(const char *s) {
	int len = 0;
	char c = *s;

	while (c != '\0') {
		c = *(s++);
		len++;
	}
	return len;
}

