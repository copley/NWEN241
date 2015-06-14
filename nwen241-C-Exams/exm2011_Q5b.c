#include <stdio.h>

int is_within(const char *str, char ch){
	while((*str)!='\0'){
		printf("%c",*str);
		if (ch == *str++){ return 1;}
	}
	return 0;
}

int main(void){
	char *str = {"qwertyuiop"};
	char ch = 'r';
	printf("%d",is_within(str, ch));
}