#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "../parse/parser.h"
#include "memory.h"
#include "Vtree.h"
#include "context.h"
#include "../lang/method.h"
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

	return t;
}

int lamdaNum = 0;
Contexts* lamdaContexts[MAX_LAMDA_NUM];

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
	Contexts* contexts = newContexts();
	pushContext(contexts, global);

	Method* methods[MAX_METHOD_NUM] = {
		defineMethod("+", method_add),
		defineMethod("add", method_add),
		defineMethod("-", method_minus),
		defineMethod("minus", method_minus),
		defineMethod("*", method_multiply),
		defineMethod("multiply", method_multiply),
		defineMethod("/", method_divide),
		defineMethod("divide", method_divide),
		defineMethod("\\", method_last),
		defineMethod("last", method_last)
	};

	return execute(code, vm, contexts, methods);
}

int calc(Vnode* expr, VM* vm, Contexts* contexts, Method** methods){
	// Already calculated
	if(expr->obj){
		return 0;
	}

	// Variable
	if(expr->name){
		if(strEqual(expr->name, "assign") || strEqual(expr->name, "$") || strEqual(expr->name, "lamda")){
			expr->isMethod = true;
		}else{
			for(int i = 0; methods[i]; i++){
				if(strEqual(expr->name, methods[i]->name)){
					expr->isMethod = true;
					break;
				}
			}
		}

		if(!expr->isMethod){
			expr->obj = findFromContexts(contexts, expr->name);
			assert(expr->obj, "Error: %s not defined!", expr->name);
		}
	}

	// Calculate
	if(expr->childrenNum){
		calc(expr->children[0], vm, contexts, methods);

		Vnode* firstNode = expr->children[0];
		int argNum = expr->childrenNum - 1;

		printf("====================== Calc =======================\n");
		printf("Calc: %s \n", firstNode->name);
		printContexts(contexts);
		printf("End : %s\n", firstNode->name);

		// Native method
		if(firstNode->isMethod){
			if(strEqual(firstNode->name, "assign") || strEqual(firstNode->name, "$")){
				assert(argNum == 2 && expr->children[1]->name, "Error: Wrong arguments for def!");

				char* key = expr->children[1]->name;
				calc(expr->children[2], vm, contexts, methods);
				Object* value = expr->children[2]->obj;
				Context* curr = getTopContext(contexts);

				defineInContext(curr, key, value);
			}else if(strEqual(firstNode->name, "lamda")){
				expr->obj = pushLamda(vm, expr->node);
				expr->obj->lamdaId = lamdaNum;
				lamdaContexts[lamdaNum] = copyContexts(contexts, NULL);
				lamdaNum++;
			}else{
				for(int i = 0; methods[i]; i++){
					if(strEqual(firstNode->name, methods[i]->name)){
						Object** args = malloc(sizeof(Object*) * argNum);
						for(int i = 0; i < argNum; i++){
							calc(expr->children[i+1], vm, contexts, methods);
							args[i] = cloneObject(vm, expr->children[i+1]->obj);
						}
						expr->obj = methods[i]->callee(argNum, args, vm);
						break;
					}
				}
			}
			return 0;
		}

		Object* firstVal = firstNode->obj;

		// First value
		if(firstVal->type != OBJ_LAMDA){
			expr->obj = cloneObject(vm, firstVal);
			return 0;
		}

		// Lamda call
		// get args
		Contexts* cxts = copyContexts(lamdaContexts[firstVal->lamdaId], NULL);
		Context* runCxt = newContext();
		for(int i = 0; i < argNum; i++){
			calc(expr->children[i+1], vm, contexts, methods);
			defineInContext(runCxt, firstVal->args[i], cloneObject(vm, expr->children[i+1]->obj));
		}
		pushContext(cxts, runCxt);
		Vnode* vn = getVnode(firstVal->grammarTree->root, vm);
		calc(vn, vm, cxts, methods);
		expr->obj = vn->obj;

		return 0;
	}

	return 0;
}

int execute(char* code, VM* vm, Contexts* contexts, Method** methods){
	Tree* tree = parse(code);
	printNode(tree->root, 0);

	Vtree* vtree = getVtree(tree, vm);
	//printVnode(vtree->root, 0);

	calc(vtree->root, vm, contexts, methods);
	printVnode(vtree->root, 0);

	printf(">>>>> ");
	printObject(vtree->root->obj, 0);
	printf("\n");

	return 0;
}