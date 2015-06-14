#include <stdio.h>

int string_lenght(char *str){
	int n=0;
	char c;
	while (*str !='\0'){
		str++;
		n++;
	}
	return n;
}

int main(void){
	char *str = "neve";
	printf("%s is %d char long\n", str, string_lenght(str));
	return 0;
}