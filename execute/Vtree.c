#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../util/tree.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "memory.h"
#include "Vtree.h"

void printVnode(Vnode* node, int depth){

	if(node->name){
		printTab(depth);
		printf("Name: %s, ", node->name);
		printf("\n");
	}

	if(node->obj){
		printTab(depth);
		printObject(node->obj, depth);
		printf("\n");
	}
	printTab(depth);
	printf("Children num: %d\n\n", node->childrenNum);

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
	n->isMethod = false;

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
