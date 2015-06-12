#include <stdio.h>

void func(char *);

void func(char *str){
	char *tmp = str;
	int size = sizeof(str)/sizeof(char);
	int i;

	for (i=0; i<size; i++){
		printf("%s",tmp);
		tmp++;
	}
}

int main(void){
	func("Diego\n");
}


