#ifndef _SYNTAX_PARSER_H
#define _SYNTAX_PARSER_H

#define MAX_CHILDREN_NUM 100
#define MAX_STRING_LENGTH 100

typedef struct {
	union {
		int num;
		char* str;
	} data;

	enum {
		VALUE_TYPE_NUM,
		VALUE_TYPE_BOOL,
		VALUE_TYPE_STRING
	} type;
} Value;

typedef struct _Node {
	struct _Node** children;
	int childrenNum;

	Value* val;
} Node;

typedef struct {
	Node* root;
} Tree;

void printNode(Node* node, int depth){
	for(int i = 0; i < depth; i++){
		printf("\t");
	}
	printf("Type: %d, Val: %s, Children num: %d\n", node->val->type, node->val->data.str, node->childrenNum);

	for(int j = 0; j < node->childrenNum; j++){
		printNode(node->children[j], depth+1);
	}
}

Value* newValue(){
	Value* v = malloc(sizeof(Value));
	return v;
}

Node* newNode(){
	Node* n = malloc(sizeof(Node));
	n->children = NULL;
	n->childrenNum = 0;
	n->val = newValue();
	return n;
}

Tree* newTree(){
	Tree* t = malloc(sizeof(Tree));
	t->root = newNode();
	return t;
}

int addChild(Node* parent, Node* child){
	if(parent->childrenNum >= MAX_CHILDREN_NUM){
		// too many children
		printf("Error: node has too many children!!!");
		return 1;
	}

	if(parent->children == NULL){
		parent->children = malloc(sizeof(Node) * MAX_CHILDREN_NUM);
	}

	parent->children[parent->childrenNum] = child;
	parent->childrenNum++;

	return 0;
}



#endif
