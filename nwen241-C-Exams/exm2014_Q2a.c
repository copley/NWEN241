#include <stdio.h>

void func(char *);

void func(char *c){
	while(*c != '\0'){
		printf("%s",c);
		c++;
	}
}

int main(void){
	func("Diego");
}



