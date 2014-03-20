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
		VALUE_TYPE_OP,
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

void printNode(Node* node, int depth);

Value* newValue();

Node* newNode();

Tree* newTree();

int addChild(Node* parent, Node* child);

#endif
