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

Object* getObject(Value* value, VM* vm){
	Object* object = NULL;

	switch(value->type){
		case VALUE_TYPE_NULL:
			break;

		case VALUE_TYPE_NUM:
			object = pushInt(vm, parseNum(value->data, 10));
			break;

		case VALUE_TYPE_STRING:
			object = pushString(vm, parseString(value->data));
			break;

		case VALUE_TYPE_OP:
			break;

		case VALUE_TYPE_VAR:
			break;
	}

	return object;
}

Vnode* getVnode(Node* node, VM* vm){
	if(!node){
		return NULL;
	}

	Vnode* n = newVnode();

	n->obj = getObject(node->val, vm);

	n->node = node;

	if(node->val->type == VALUE_TYPE_OP || node->val->type == VALUE_TYPE_VAR){
		n->name = strCopy(node->val->data, NULL);
	}

	for(int i = 0; i < node->childrenNum; i++){
		addVchild(n, getVnode(node->children[i], vm));
	}

	return n;
}

Vtree* getVtree(Tree* tree, VM* vm){
	Vtree* t = newVtree();

	t->root = getVnode(tree->root, vm);
}

int main(int argc, const char * argv[]) {
	char code[1000] = "";

	FILE *fp = fopen(argv[1], "r");
	int i = 0;
	char c;
	while((c = fgetc(fp)) != EOF){
		code[i++] = c;
	}
	fclose(fp);
	code[i] = '\0';

	VM* vm = newVM();
	Context* global = newContext();
	Context* contextStack[CALL_STACK_SIZE] = {global};
	int curr = 0;

	Tree* tree = parse(code);
	printNode(tree->root, 0);
	printVnode(getVnode(tree->root, vm), 0);
}


int calc(Vnode* expr, VM* vm){
	
};

int execute(char* code, VM* vm){
	return 0;
}