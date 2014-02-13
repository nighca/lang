#ifndef _CONTEXT_H
#define _CONTEXT_H

typedef struct {

} Context;

Context* newContext();

Object* findFromContext(Context* context, char* key);

int defineInContext(Context* context, char* key, Object* object);

#endif