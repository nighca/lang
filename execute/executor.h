#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#define CALL_STACK_SIZE 100

Object* getObject(Value* value, VM* vm);

Vnode* getVnode(Node* node, VM* vm);

Vtree* getVtree(Tree* tree, VM* vm);

int calc(Vnode* expr, VM* vm);

int execute(char* code, VM* vm);

#endif