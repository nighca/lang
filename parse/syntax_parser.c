#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../util/tree.h"
#include "token_parser.h"
#include "syntax_parser.h"

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
	n->val = newValue();

	_initNode(n);

	return n;
}

Tree* newTree(){
	Tree* t = malloc(sizeof(Tree));

	_initTree(t, newNode);

	return t;
}

int addChild(Node* parent, Node* child){
	_addChild(parent, child, Node, MAX_CHILDREN_NUM);

	return 0;
}

/*
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
*/

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