#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "../parse/parser.h"
#include "memory.h"
#include "Vtree.h"
#include "context.h"
#include "executor.h"

VM* vm = newVM();
Context* global = newContext();
Context* contextStack[CALL_STACK_SIZE] = {global};
int curr = 0;

Object* getObject(Value* value){
	Object* object = NULL;

	switch(value->type){
		case VALUE_TYPE_NULL:
			break;

		case VALUE_TYPE_NUM:
			object = pushInt(vm, parseNum(value->data, 10));
			break;

		case VALUE_TYPE_STRING:
			object = pushString(vm, value->data);
			break;

		case VALUE_TYPE_OP:
			break;

		case VALUE_TYPE_VAR:
			break;
	}
}

Vnode* getVnode(Node* node){
	if(!node){
		return NULL;
	}

	Vnode* n = newVnode();

	n->obj = getObject(node->value);

	n->node = node;

	if(node->value->type == VALUE_TYPE_OP || node->value->type == VALUE_TYPE_VAR){
		n->name = strCopy(node->value->data, NULL);
	}

	for(int i = 0; i < node->childrenNum; i++){
		addVchild(n, getVnode(node->children[i]));
	}

	return n;
}

Vtree* getVtree(Tree* tree){
	Vtree* t = newVtree();

	t->root = getVnode(tree->root);
}

/*int main(int argc, const char * argv[]) {
	char code[1000] = "";
	gets(code);

	Tree* tree = parse(code);
	printNode(tree->root, 0);
}
*/

int calc(Node* expr){
	
};

int execute(char* code){
	return 0;
}