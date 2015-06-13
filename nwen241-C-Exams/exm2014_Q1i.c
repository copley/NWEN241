#include <stdio.h>

typedef union {
int i;	
char c;
char *p;
} int_char;

int main(void){
	printf("%d",sizeof(int_char));
}