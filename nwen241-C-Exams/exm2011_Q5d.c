#include <stdio.h>
#include <stdlib.h>

void removes(FILE *fp1, FILE *fp2){
	char c;
	while ((c=fgetc(fp1))!=EOF){
		if (c == 'e' || c == 'E');
		else{
			fprintf(fp2, "%c", c);
		}
	}
}

int main(int argc, char **argv){
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "w");
	removes(fp1,fp2);
}