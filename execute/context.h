#ifndef _CONTEXT_H
#define _CONTEXT_H

#define MAX_DEF_NUM_IN_CONTEXT 100
#define MAX_CONTEXT_STACK_SIZE 100

typedef struct {
	char* names[MAX_DEF_NUM_IN_CONTEXT];
	Object* objs[MAX_DEF_NUM_IN_CONTEXT];

	int varNum;
} Context;

typedef struct {
	Context* stack[MAX_CONTEXT_STACK_SIZE];
	int stackSize;
} Contexts;

Context* newContext();

void printContext(Context* context);

Object* findFromContext(Context* context, char* key);

int defineInContext(Context* context, char* key, Object* object);

Contexts* newContexts();

void printContexts(Contexts* contexts);

int pushContext(Contexts* contexts, Context* context);

Context* popContext(Contexts* contexts);

Context* getTopContext(Contexts* contexts);

Contexts* copyContexts(Contexts* from, Contexts* to);

Object* findFromContexts(Contexts* contexts, char* key);

#endif