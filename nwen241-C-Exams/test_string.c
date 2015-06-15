#include <stdio.h>

int main(void){
	char str[] = "Diego\n";
	printf("%s",str);
	int i;
	for (i=0;str[i]!='\0';i++){
		str[i] = printf("%d",i+1);
	}
	printf("%s",str);
}