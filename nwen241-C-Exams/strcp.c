#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	// if you use an [] notation can query sizeof, whereas if you use pointer can call strlen
	char *str = "bla-lal -lalalal a";
	char *str2 = malloc(strlen(str)+1*sizeof(char));
	strcpy(str2, str);
	printf("%s\n",str2);
	return 0;
}