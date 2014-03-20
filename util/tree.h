#ifndef _TREE_H
#define _TREE_H

#define _initNode(node) \
(node)->children = NULL; \
(node)->childrenNum = 0;

#define _initTree(tree, newnode) \
(tree)->root = newnode();

#define _addChild(parent, child, type, max) \
assert((parent)->childrenNum < (max), "Error: node has too many children!!!"); \
if((parent)->children == NULL){ \
	(parent)->children = malloc(sizeof(type *) * (max)); \
} \
 \
(parent)->children[(parent)->childrenNum] = (child); \
(parent)->childrenNum++;

#endif