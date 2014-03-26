#ifndef _METHOD_H
#define _METHOD_H

#define getArgs(argNum, nodes, args) \
{ \
	args = malloc(sizeof(Object*) * (argNum)); \
	for(int i = 0; i < (argNum); i++){ \
		calc((nodes)[i+1], vm, contexts, methods); \
		//args[i] = cloneObject(vm, (nodes)[i]->obj, NULL); \
		args[i] = (nodes)[i+1]->obj; \
	} \
}

typedef struct {
	char* name;
	Object* (*callee)(int, Object**, VM*);
} Method;

Method* defineMethod(char* name, Object* (*callee)(int, Object**, VM*));

Object* method_add(int argNum, Object** args, VM* vm);

Object* method_minus(int argNum, Object** args, VM* vm);

Object* method_multiply(int argNum, Object** args, VM* vm);

Object* method_divide(int argNum, Object** args, VM* vm);

Object* method_last(int argNum, Object** args, VM* vm);

#endif