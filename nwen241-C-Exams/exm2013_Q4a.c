#include <stdio.h>

int main(void){
	int m[4][4] = {{1,3,5,7},{11,33,55,77},{2,4,6,8},{22,44,66,88}};
	int (*parr)[4] = m;
	int a[3] = {11,22,33};
	int *pa = a;

	printf("m[4][4] = {{1,3,5,7},{11,33,55,77},{2,4,6,8},{22,44,66,88}};\n");
	printf("(*parr)[4] = m;\n");
	printf("a[3] = {11,22,33};\n");

	printf("*a = %d\n",*a);
	printf("*a = %d\n",*(a+2));
	printf("*a = %d\n",*pa);
	printf("*a = %d\n",pa[1]);
	printf("*a = %d\n",**m);
	printf("*a = %d\n",*(*m+2));
	printf("*a = %d\n",*(*(m+1)+1));
	printf("*a = %d\n",*(m[1]+2));
	printf("*a = %d\n",(*(m+2))[3]);
	printf("*a = %d\n",(*(parr+3))[2]);
}

