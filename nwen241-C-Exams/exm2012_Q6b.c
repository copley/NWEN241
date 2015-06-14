#include <stdio.h>
#include <string.h>

void swapChar(char x[], char y[]){
	int size = strlen(x);
	int i;

	for (i=0; i<size; i++){
	printf("----");
		if (x[i] != y[i]){
			x[i] ^= y[i];
			y[i] ^= x[i];
			x[i] ^= y[i];
		}
	}
}

int main(void){
	char x[] = "abc";
	char y[] = "def";
	printf("%s %s\n",x,y);
	swapChar(x, y);
	printf("%s %s\n",x,y);
	return 0;
}