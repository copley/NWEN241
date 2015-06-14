#include <stdio.h>
#include <string.h>

int string_reverse(char *str){
	int size = strlen(str);
	int i;
	char c;

	for (i=0;i<=size/2;i++){
		c = str[size-i-1];
		str[size-i-1] = str[i];
		str[i] = c;
	}
	return 0;
}

int main(void){
	char str[] = "ABCDEFG";
	printf("%s\n",str);
	string_reverse(str);
	printf("%s\n",str);
}