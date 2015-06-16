#include <stdio.h>

typedef union {
int i;	
char c;
char *p;
} int_char;

typedef struct {
	int age;
	char gender;
	char *name;
} Person;

int main(void){
	printf("%d\n",sizeof(Person));
	printf("%d\n",sizeof(int_char));
}