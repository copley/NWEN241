#include <stdio.h>

typedef struct {
	int agel;
	char gender;
	char *name;
} Person;

typedef union {
	int i;
	char c;
	char *p;
	char ff[17];
} int_char;

int main(void){
	printf("\n%d\n",(int)sizeof(int_char));
	char ff[9];
	printf("%d\n",(int)sizeof(ff));
}