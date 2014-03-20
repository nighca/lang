#ifndef _VTREE_H
#define _VTREE_H

#define MAX_CHILDREN_NUM 100
#define MAX_STRING_LENGTH 100
#define MAX_MEM_STACK_SIZE 500

typedef struct _Vnode {
	struct _Vnode** children;
	int childrenNum;

	Object* obj;
	Node* node;
	char* name;
} Vnode;

typedef struct {
	Vnode* root;
} Vtree;

void printVnode(Vnode* node, int depth);

Vnode* newVnode();

Vtree* newVtree();

int addChild(Vnode* parent, Vnode* child);

#endif
