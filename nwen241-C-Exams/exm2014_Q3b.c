#define Node_Size sizeof(Node)
#define NULL 0
#include <stdlib.h>
#include <stdio.h>

typedef char Data; // defines char as Data

typedef struct node { // creates a struct names struct
	Data data; // which contains data
	struct node *next; // and a pointer to next node
} Node; // then renames the structure to Node

typedef Node *ptrNode; // creates a pointed to node to use it head/tail

typedef struct queue // creates a struct contrianing front/back and count
{
	int cnt;
	ptrNode front;
	ptrNode back;
} Queue; // then renames it to Queue

void enqueue(Data d, Queue *q){

	if (q->cnt == 0){
		q->cnt = 1;
		q->front = q->back;
	} else {
		ptrNode n = malloc(sizeof(Node));
		n->data = d;
		n->next = NULL;
		q->back->next = n;
		q->back = n;
		(q->cnt)++;	
	}
}

Data dequeue(Queue *);

void printList(Queue *q){
	ptrNode pl = q->front;
	while (pl!=NULL){
		printf("%c",pl->data);
		pl=pl->next;
	}
}

int main(void){
	Queue q;
	Data d = 'f';
	enqueue(d, &q);
	printList(&q);
}


