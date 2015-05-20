/*
 * q3.c
 *
 *  Created on: 19/05/2015
 *      Author: diego
 */

int main(void){
	char *pa[] = {"12", "34", "56"};
	int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
	int (*ppm)[2][3] = &m;
	int *a;
	int b = 2;
	int *p = &b;

	printf("sizeof(int) = %d\n", sizeof(b));
	printf("sizeof(char) = %d\n", sizeof('c'));
	printf("sizeof(pointer) = %d\n\n", sizeof(p));

	printf("sizeof(pa) = %d\n",sizeof(pa));
	printf("sizeof(*pa) = %d\n",sizeof(*pa));
	printf("sizeof(**pa) = %d\n",sizeof(**pa));
	printf("sizeof(ppm) = %d\n",sizeof(ppm));
	printf("sizeof(*ppm) = %d\n",sizeof(*ppm));
	printf("sizeof(**ppm) = %d\n",sizeof(**ppm));
}

