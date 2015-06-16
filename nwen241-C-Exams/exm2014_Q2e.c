
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

void swap2(char a1[], char a2[]){
	int i;
	int size = strlen(a1);
	for(i=0;i<size;i++){
		if(a1[i]!=a2[i]){
			a1[i]^=a2[i];
			a2[i]^=a1[i];
			a1[i]^=a2[i];
		}
	}
}

int main(void){
	char a1[] = "black";
	char a2[] = "white";

	printf("%s, %s\n", a1,a2);
	swap2(a1,a2);
	printf("%s, %s\n", a1,a2);
	return 0;
}