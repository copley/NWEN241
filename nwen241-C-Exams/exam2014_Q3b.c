#define Node_Size sizeof(Node)

typedef char Data;

typedef struct node {
	Data data;
	struct node *next;
} Node;

typedef Node* ptrNode

