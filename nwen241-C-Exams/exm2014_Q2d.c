#include <stdio.h>

int func(char c, const char * str){
//	char *tmp = str;
	while (*str != '\0'){
		if (c == *str){
			printf("%c",*str);
			return 1;
		}
		str++;
	}
	return 0;
}

int main(void){
	printf("%d",func('i',"Diego\n"));
}


