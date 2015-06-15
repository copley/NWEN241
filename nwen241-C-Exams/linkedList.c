#include <stdio.h>
#include <stdlib.h>
#define Node_size sizeof(Node)

typedef struct node {
	char data;
	struct node *next;
} Node;

typedef Node *ptrNode;

ptrNode createlisti(char *str){
	// make head and tail 
	int i;
	ptrNode head, tail;
	// create head and attach tail, then work on tail to add data and next
	if (str[0]!='\0'){
		head = malloc(Node_size);
		tail = head;
		tail->data = str[0];
	// create other nodes working on tail
		for (i=1;str[i]!='\0';i++){
			tail->next = malloc(Node_size);
			tail = tail->next;
			tail->data = str[i];
			tail->next = NULL;
		}
	}
	// return head
	return head;
}

ptrNode createlistr(char *str){
	// base case
	if (str[0] == '\0') return NULL;
	else {
		ptrNode pnode = malloc(Node_size);
		pnode->data = str[0];
		pnode->next = createlistr(&str[1]);
		return pnode;
	} 

}

void printlist(ptrNode node){
	while (node->next!=NULL){
		printf("Node: %c\n",node->data);
		node = node->next;
	}
	printf("Node: %c\n",node->data);
}

int main(void){
	ptrNode head = createlistr("Diego");
	printlist(head);
}