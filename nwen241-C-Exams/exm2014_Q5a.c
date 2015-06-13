#include <stdio.h>

int main(int argc, char **argv){
	char c;
	printf("%s",argv[1]);
	FILE *f1 = fopen("./file1.txt", "r");
	FILE *f2 = fopen(argv[2], "w");
	while ((c=fgetc(f1))!=EOF){
		printf("%c",c);
		fprintf(f2,"%c",c);
	}
}
