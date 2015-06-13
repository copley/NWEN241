#include <stdio.h>
#include <string.h>

int main(void){
	char *text = "Some text to write in binary";
	char **pText = &text;

	FILE *fp = fopen("./file2.bin", "w");

	if (fp != NULL){
		fwrite(text, strlen(text)+sizeof(char), 1, fp);
	} else {
		fprintf(stderr, "Error while accessing file");
	}
}