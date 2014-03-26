#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#define CALL_STACK_SIZE 100
#define MAX_METHOD_NUM 100
#define MAX_LAMDA_NUM 1000

Object* getObject(Value* value, VM* vm);

Vnode* getVnode(Node* node, VM* vm);

Vtree* getVtree(Tree* tree, VM* vm);

int calc(Vnode* expr, VM* vm, Contexts* contexts, Method** methods);

int execute(char* code, VM* vm, Contexts* contexts, Method** methods);

#endif