#include <stdio.h>

int main(void) {
	char m[5][7] = {"abcdef", "ghijkl", "mnopqr", "stuvwx", "yz"};
	char (*p)[7] = m;
	printf("%c\n", **m);
	printf("%c\n", *(*m+2));
	printf("%c\n", *(*(m+1)+1));
	printf("%c\n", *(m[1]+2));
	printf("%c\n", (*(m+2))[3]);
	printf("%c\n", (*(p+3))[2]);
	p++; printf("%d\n", (int)p - (int)m);
}
