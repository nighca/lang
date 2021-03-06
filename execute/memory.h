#ifndef _MEMORY_H
#define _MEMORY_H

#define STACK_MAX 256
#define MAX_STRING_LENGTH 100
#define MAX_LIST_LENGTH 100
#define MAX_ARGS_NUM 100

typedef enum {
	OBJ_INT,
	OBJ_STRING,
	OBJ_LIST,
	OBJ_LAMDA,
	OBJ_METHOD
} ObjectType;

typedef struct _Object {
	struct _Object* next;

	ObjectType type;

	union {
		/* OBJ_INT */
		int val;

		/* OBJ_STRING */
		char str[MAX_STRING_LENGTH];

		/* OBJ_LIST */
		struct {
			struct _Object* sons[MAX_LIST_LENGTH];
			int length;
		};

		/* OBJ_LAMDA */
		struct {
			int lamdaId;
			char* args[MAX_ARGS_NUM];
			int argsNum;
			Tree* grammarTree;
		};
	};
} Object;

typedef struct {
	int numObjects;
	int maxObjects;

	Object* firstObject;

	Object* stack[STACK_MAX];
	int stackSize;
} VM;

VM* newVM();

void push(VM* vm, Object* value);

Object* pop(VM* vm);

Object* newObject(VM* vm, ObjectType type);

void printObject(Object* obj, int depth);

Object* cloneObject(VM* vm, Object* obj);

Object* pushInt(VM* vm, int val);

Object* pushString(VM* vm, char* str);

Object* pushList(VM* vm, int length);

Object* pushLamda(VM* vm, Node* lamdaNode);

int listPushItem(Object* parent, Object* son);

#endif