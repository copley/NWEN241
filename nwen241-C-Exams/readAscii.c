#include <stdio.h>

int main(void){
	char c;
	FILE *fp = fopen("./file1.txt","r");
	while ((c=fgetc(fp))!=EOF){
		fprintf(stdout, "%c",c);
	}
	return 0;
}