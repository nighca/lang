#ifndef _CONTEXT_H
#define _CONTEXT_H

#define MAX_DEF_NUM_IN_CONTEXT 100


typedef struct {
	char* names[MAX_DEF_NUM_IN_CONTEXT];
	Object* objs[MAX_DEF_NUM_IN_CONTEXT];

	int varNum;
} Context;

Context* newContext();

Object* findFromContext(Context* context, char* key);

int defineInContext(Context* context, char* key, Object* object);

#endif