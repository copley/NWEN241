#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	char *str1 = "oggi vado ";
	char *str2 = "allo stadio";

	char *str3 = calloc(sizeof(char), strlen(str1)+strlen(str2));

	strcat(str3,str1);
	strcat(str3,str2);

	printf("%s\n",str3);
}