#include <stdio.h>
#include <stdlib.h>
#define Node_size sizeof(Node)

typedef struct node {
	char data;
	struct node *next;
} Node;

typedef Node *ptrNode;

ptrNode createlisti(char *str){
	// make a head and a tail
	ptrNode head;
	ptrNode tail;
	// assign mem to head and point tail to head
	head = malloc(Node_size);
	tail = head;
	tail->data = *str;
	int i;
	// while(*++str!='\0'){
	for (i=1; str[i]!='\0';i++) {
		tail->next = malloc(Node_size);
		tail = tail->next;
		tail->data = str[i];
		// str++;
	}
	tail->next = NULL;
	return head;
}

ptrNode createlistr(char *str){
	// base case
	if (*str=='\0'){
		return NULL;
		// ptrNode node = malloc(Node_size);
		// node->data = *str;
		// node->next = NULL;
		// return node;
	} else {
		ptrNode node = malloc(Node_size);
		node->data = *str;
		node->next = createlistr(str+1);
		return node;
	}
}

void printlist(Node *n){
	while(n->next != NULL){
		printf("Node: %c\n",n->data);
		n = n->next;
	}
	printf("Node: %c\n",n->data);
}


int main(void){
	ptrNode head = createlisti("Diego");
	printlist(head);
}

