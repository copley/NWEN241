#include <stdio.h>
#include <string.h>

void swap(char a1[], char a2[]){
	int i = 0;
	while (a1[i] != '\0'){
		char c;
		c = a1[i];
		a1[i] = a2[i];
		a2[i] = c;
		i++;
	}
}

int main(void){
	char a1[] = "black";
	char a2[] = "white";

	printf("%s, %s\n", a1,a2);
	swap(a1,a2);
	printf("%s, %s\n", a1,a2);
	return 0;
}