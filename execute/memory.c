#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "memory.h"

VM* newVM() {
	VM* vm = malloc(sizeof(VM));
	vm->stackSize = 0;
	vm->firstObject = NULL;
	vm->numObjects = 0;

	return vm;
}

void pushObject(VM* vm, Object* value){
	assert(vm->stackSize < STACK_MAX, "Error: Stack overflow!");
	vm->stack[vm->stackSize++] = value;
}

Object* popObject(VM* vm){
	assert(vm->stackSize > 0, "Error: Stack underflow!");
	return vm->stack[--vm->stackSize];
}

Object* newObject(VM* vm, ObjectType type){
	Object* object = malloc(sizeof(Object));
	object->type = type;

	object->next = vm->firstObject;
	vm->firstObject = object;

	vm->numObjects++;

	return object;
}

Object* pushInt(VM* vm, int val){
	Object* object = newObject(vm, OBJ_INT);
	object->val = intValue;
	pushObject(vm, object);

	return object;
}

Object* pushString(VM* vm, char* str){
	Object* object = newObject(vm, OBJ_STRING);
	
	int i = 0;
	for(; str[i]; i++){
		object->str[i] = str[i];
	}

	assert(i < MAX_STRING_LENGTH, "Error: Too long string!");
	object->str[i] = '\0';

	pushObject(vm, object);

	return object;
}

Object* pushList(VM* vm, int length){
	Object* object = newObject(vm, OBJ_LIST);
	
	while(length--){
		listPushItem(object, popObject(vm));
	}
	pushObject(vm, object);

	return object;
}

int listPushItem(Qbject* parent, Qbject* son){
	assert(parent->length < MAX_LIST_LENGTH, "Error: Too long list!");
	parent->sons[parent->length++] = son;

	return parent->length;
}
