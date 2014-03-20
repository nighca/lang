#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../util/tree.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "memory.h"
#include "Vtree.h"

void printObject(Object* obj, int depth){
	for(int i = 0; i < depth; i++){
		printf("\t");
	}

	printf("Type: %d, ", obj->type);
	switch(obj->type){
		case OBJ_INT:
			printf("Value: %d", obj->val);
			break;

		case OBJ_STRING:
			printf("Value: %s", obj->str);
			break;

		case OBJ_LIST:
			printf("Value: List(%d)", obj->length);
			break;

		case OBJ_LAMDA:
			printf("Value: Lamda(%d)", obj->argsNum);
			break;
	}
	printf("\n");
};

void printVnode(Vnode* node, int depth){
	for(int i = 0; i < depth; i++){
		printf("\t");
	}

	if(node->name){
		printf("Name: %s, ", node->name);
	}

	if(node->obj){
		printf("\n");
		printObject(node->obj, depth);

		for(int i = 0; i < depth; i++){
			printf("\t");
		}
	}
	printf("Children num: %d\n", node->childrenNum);

	for(int j = 0; j < node->childrenNum; j++){
		printVnode(node->children[j], depth+1);
	}

	printf("\n");
}

Vnode* newVnode(){
	Vnode* n = malloc(sizeof(Vnode));
	n->obj = NULL;
	n->node = NULL;
	n->name = NULL;

	_initNode(n);

	return n;
}

Vtree* newVtree(){
	Vtree* t = malloc(sizeof(Vtree));

	_initTree(t, newVnode);

	return t;
}

int addVchild(Vnode* parent, Vnode* child){
	_addChild(parent, child, Vnode*, MAX_CHILDREN_NUM);

	return 0;
}
