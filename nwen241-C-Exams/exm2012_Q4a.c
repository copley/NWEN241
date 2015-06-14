#include <stdio.h>

int main(void){
	char m[5][6] = {"01234", "56789", "abcde", "fghij", "klmno"};
	printf("%c\n", *(&m[0][0]+9));
}