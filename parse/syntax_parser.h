#ifndef _SYNTAX_PARSER_H
#define _SYNTAX_PARSER_H

#define MAX_CHILDREN_NUM 100
#define MAX_STRING_LENGTH 100

typedef struct {
	union {
		int num;
		char* str;
		char* name;
	} data;

	enum {
		VALUE_TYPE_NULL,
		VALUE_TYPE_NUM,
		VALUE_TYPE_STRING,
		VALUE_TYPE_LAMDA
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

void printValue(Value* val){
	switch(val->type){
	case VALUE_TYPE_NUM:
		printf("Val: %d, ", val->data.num);
		break;
	case VALUE_TYPE_NULL:
		printf("Val: %s, ", "NULL");
		break;
	case VALUE_TYPE_STRING:
		printf("Val: %s, ", val->data.str);
		break;
	case VALUE_TYPE_LAMDA:
		printf("Val: %s, ", val->data.name);
		break;
	}
}

void printNode(Node* node, int depth){
	for(int i = 0; i < depth; i++){
		printf("\t");
	}

	printf("Type: %d, ", node->val->type);
	printValue(node->val);
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

int parseNum(char* input){
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
}

int callLamda(Value* lamda, Value** args, int argsNum, Value* result){
	if(argsNum){
		result->type = args[0]->type;
		result->data = args[0]->data;
	}else{
		// do nothing
	}

	return 0;
}

Node* calc(Node* node){
	//printValue(node->val);
	//printf("\n");

	if(node->val->type == VALUE_TYPE_NULL){
		if(node->identifier){
			node->val = getValFromContext()
		}else if(node->childrenNum){
			Value* lamda = node->children[0]->val;
			int argsNum = node->childrenNum - 1;
			Value** args = (Value**)malloc(sizeof(Value*) * argsNum);
			for(int i = 0; i < argsNum; i++){
				args[i] = calc(node->children[i+1])->val;
			}

			callLamda(lamda, args, argsNum, node->val);
		}
	}

	return node;
}

#endif
