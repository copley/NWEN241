#include <stdio.h>

int func(int **bla){
	printf("%d\n",**bla);
	return 0;
}

int main(void){
	printf("Assigment check:\n");
	// int a[2][4];
	// int (*d)[20];
	int a = 3;
	int *c[20];
	c[0] = &a;
	int **d;
	func(d);
}


