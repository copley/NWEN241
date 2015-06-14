#include <stdio.h>

int main(void){
	char m[4][6] = {"ABCDE","FGHIJ","KLMNO","PQRST"};

	printf("\n**m : %c",**m);
	printf("\n*(*m+2) %c",*(*m+2));
	printf("\n*(*(m+1)+1)) %c",*(*(m+1)+1));
	printf("\n*(m[1]+2)) %c",*(m[1]+2));
	printf("\n*(m+2))[3]) %c",(*(m+2))[3]);
	printf("\n&m[0][0]+9 %c\n",*(&m[0][0]+9)); // &m[0][0]+9 I
}