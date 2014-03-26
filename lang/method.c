#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "../parse/parser.h"
#include "../execute/memory.h"
#include "../execute/Vtree.h"
#include "../execute/context.h"
#include "method.h"

Method* defineMethod(char* name, Object* (*callee)(int, Object**, VM*)){
	Method* method = malloc(sizeof(Method));

	method->name = strCopy(name, NULL);
	method->callee = callee;

	return method;
}

Object* method_add(int argNum, Object** args, VM* vm){
	assert(argNum > 0, "Error: Arguments needed!");

	Object* result = NULL;

	switch(args[0]->type){
		case OBJ_INT: {
			int sum = args[0]->val;

			for(int i = 1; i < argNum; i++){
				switch(args[i]->type){
					case OBJ_INT: {
						sum += args[i]->val;
					}
					break;
					case OBJ_STRING: {
						sum += stoi(args[i]->str, 10);
					}
					break;
					default:;
				}
			}

			result = pushInt(vm, sum);
		}
		break;

		case OBJ_STRING: {
			char* sum = strCopy(args[0]->str, NULL);

			for(int i = 1; i < argNum; i++){
				switch(args[i]->type){
					case OBJ_INT: {
						sum = strConcat(sum, itos(args[i]->val, 10));
					}
					break;
					case OBJ_STRING: {
						sum = strConcat(sum, args[i]->str);
					}
					break;
					default:;
				}
			}

			result = pushString(vm, sum);
		}
		break;

		case OBJ_LIST:
		default:;
	}
	
	return result;
}

Object* method_minus(int argNum, Object** args, VM* vm){
	assert(argNum > 0, "Error: Arguments needed!");

	Object* result = NULL;

	switch(args[0]->type){
		case OBJ_INT: {
			if(argNum == 1){
				result = pushInt(vm, 0 - args[0]->val);
				break;
			}else{
				switch(args[1]->type){
					case OBJ_INT: {
						result = pushInt(vm, args[0]->val - args[1]->val);
					}
					break;
					case OBJ_STRING: {
						result = pushInt(vm, args[0]->val - stoi(args[1]->str, 10));
					}
					break;
					default:;
				}
			}
		}
		break;

		case OBJ_STRING:
		case OBJ_LIST:
		default:;
	}
	
	return result;
}

Object* method_multiply(int argNum, Object** args, VM* vm){

}

Object* method_divide(int argNum, Object** args, VM* vm){

}

Object* method_last(int argNum, Object** args, VM* vm){
	assert(argNum > 0, "Error: Arguments needed!");

	Object* result = args[argNum - 1];

	return result;
}
