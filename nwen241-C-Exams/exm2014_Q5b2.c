#include <stdio.h>

void readlistfromfile(void){

	// uses fread from "file.dat" and prints out on screen
	FILE *fp;
	fp = fopen("file.dat","r");
	Node n;
	ptrNode pn = &n;

	while(!eof(fp)){
		fread(pn, Node_size, 1, fp);
		if (!feof(fpr))
		printf("%c %h\n",pn->data, pn->next);
	}

}