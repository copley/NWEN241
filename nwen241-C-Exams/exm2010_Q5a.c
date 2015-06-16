#include <stdio.h>

void swap(char *a, char *b){
	if (*a!=*b){
		*a^=*b;
		*b^=*a;
		*a^=*b;
	}
}

int main(void){
	char *a = "abc";
	char *b = "bac";
	printf("%s %s",a,b);
	swap(&a,&b);
	printf("%s %s",a,b);
}