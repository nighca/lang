#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../parse/syntax_parser.h"
#include "memory.h"
#include "context.h"

Context* newContext(){
	Context* context = malloc(sizeof(Context));
	context->varNum = 0;

	return context;
}

void printContext(Context* context){
	printf("--------------------- Context ---------------------\n");
	for(int i = 0; i < context->varNum; i++){
		printf("* %s: \t", context->names[i]);
		printObject(context->objs[i], 1);
		printf("\n");
	}
	printf("\n");
	printf("----------------------- END -----------------------\n");
}

Object* findFromContext(Context* context, char* key){
	for(int i = 0, l = context->varNum; i < l; i++){
		if(strEqual(key, context->names[i])){
			return context->objs[i];
		}
	}

	return NULL;
}

int defineInContext(Context* context, char* key, Object* object){
	int l = context->varNum;
	for(int i = 0; i < l; i++){
		if(strEqual(key, context->names[i])){
			context->objs[i] = object;
			return 0;
		}
	}

	assert(l < MAX_DEF_NUM_IN_CONTEXT, "Error: Too many vars in context!");

	context->names[l] = strCopy(key, NULL);
	context->objs[l] = object;
	context->varNum++;
	return 0;
}

Contexts* newContexts(){
	Contexts* contexts = malloc(sizeof(Contexts));
	contexts->stackSize = 0;

	return contexts;
}

void printContexts(Contexts* contexts){
	for(int i = 0; i < contexts->stackSize; i++){
		printContext(contexts->stack[i]);
	}
}

int pushContext(Contexts* contexts, Context* context){
	int s = contexts->stackSize;
	assert(s < MAX_CONTEXT_STACK_SIZE, "Error: Context stack overflow!");

	contexts->stack[s] = context;
	return ++(contexts->stackSize);
}

Context* popContext(Contexts* contexts){
	int s = contexts->stackSize;

	if(s <= 0){
		return NULL;
	}else{
		contexts->stackSize--;
		return contexts->stack[s];
	}
}

Context* getTopContext(Contexts* contexts){
	return contexts->stackSize > 0 ? contexts->stack[contexts->stackSize - 1] : NULL;
}

Contexts* copyContexts(Contexts* from, Contexts* to){
	if(!to){
		to = newContexts();
	}

	for(int i = 0; i < from->stackSize; i++){
		pushContext(to, from->stack[i]);
	}

	return to;
}

Object* findFromContexts(Contexts* contexts, char* key){
	Object* obj = NULL;

	for(int i = contexts->stackSize - 1; i >= 0; i--){
		if(obj = findFromContext(contexts->stack[i], key)){
			return obj;
		}
	}

	return NULL;
}