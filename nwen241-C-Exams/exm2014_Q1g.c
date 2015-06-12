#include <stdio.h>

int func(int **bla){
	printf("ddsd\n");
	return 1;
}

int main(void){
	printf("bla\n");
	//int a[2][4];
	int (*d)[20];
	func(d);
}


