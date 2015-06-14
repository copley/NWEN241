#include <stdio.h>

void printbin(int n){
	int m = 1 << 31;
	int i;
	for (i=0; i<32; i++){
		if (i%8 == 0){
			printf(" ");
		}
		printf("%d",((m&n)!=0)?1:0);
		m = m >> 1;
	}
	printf("\n");
}

int main(void){
	printbin(5);
}