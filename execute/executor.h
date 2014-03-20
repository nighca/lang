#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#define CALL_STACK_SIZE 100

Object* getObject(Value* value);

Vnode* getVnode(Node* node);

Vtree* getVtree(Tree* tree);

int calc(Node* expr);

int execute(char* code);

#endif