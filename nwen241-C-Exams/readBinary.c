#include <stdio.h>
#include <string.h>

int main(void){
	char *text;
	FILE *fp = fopen("./file2.bin", "r");

	while (!feof(fp)){
		fread(text, 29, 1, fp);
	}
	fprintf(stdout, "%s", text);
}