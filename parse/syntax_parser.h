#ifndef _SYNTAX_PARSER_H
#define _SYNTAX_PARSER_H

#define MAX_CHILDREN_NUM 100
#define MAX_STRING_LENGTH 100
#define MAX_MEM_STACK_SIZE 500

typedef struct {
	char* data;

	enum {
		VALUE_TYPE_NULL,
		VALUE_TYPE_NUM,
		VALUE_TYPE_STRING,
		VALUE_TYPE_LAMDA,
		VALUE_TYPE_VAR
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

	printf("Type: %d, ", node->val->type);
	printf("Val: %s, ", node->val->data);
	printf("Children num: %d\n", node->childrenNum);

	for(int j = 0; j < node->childrenNum; j++){
		printNode(node->children[j], depth+1);
	}
}

Value* newValue(){
	Value* v = malloc(sizeof(Value));
	v->type = VALUE_TYPE_NULL;
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
		parent->children = malloc(sizeof(Node*) * MAX_CHILDREN_NUM);
	}

	parent->children[parent->childrenNum] = child;
	parent->childrenNum++;

	return 0;
}

/*int parseNum(char* input){
	int n = 0;
	char c;

	while(c = *(input++)){
		n *= 10;
		n += (c - '0');
	}
	
	return n;
}

char* parseStr(char* input){
	char* str = malloc(sizeof(char) * MAX_STRING_LENGTH);
	int i = 0;
	for(; input[i+1]; i++){
		str[i] = input[i+1];
	}
	str[--i] = '\0';

	return str;
}*/

#endif
