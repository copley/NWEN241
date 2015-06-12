#include <stdio.h>
#include <string.h>

void swap(char a1[], char a2[]){

//	int size = sizeof(a1)/sizeof(a1[0]);
//	printf("%d\n",size);

	int i = 0;
	char tmp = a1[0];

	while (tmp != '\0'){
		tmp = a1[i];
		a1[i] = a2[i];
		a2[i] = tmp;
		i++;
	}

//	for (i=0;*a1!='\0';a1++,i++){
//		char tmp = *a1;
//		*a1 = *(a2+i);
//		*(a2+i) = tmp;
//	}
}

int main(void){
	char a1[] = "black";
	char a2[] = "white";

//	int size = sizeof(a1)/sizeof(a1[0]);
//	printf("%d\n",size);

	swap(a1,a2);
	printf("%s, %s\n", a1,a2);
	return 0;
}

/*
 * That's because const char source[] in argument position is just syntactic sugar for const char *source. See, e.g., Steven Summit's C notes.
   In this particular case, you'll want to call strlen. When not dealing with strings, pass the size of the array as a separate argument.
 */

