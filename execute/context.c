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
	return 0;
}