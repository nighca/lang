#ifndef _LEXICAL_TREE_H
#define _LEXICAL_TREE_H

#define TRUE 1
#define FALSE 0

typedef int Bool;

typedef enum {
    CALC,
    ARGS,
    EXPRESSION,
    TOKEN
} LT_Node_Type;

typedef struct _LT_Node_Data{
    LT_Node_Type type;
    
} LT_Node_Data;

typedef struct _LT_Node{
    _LT_Node* child;
    _LT_Node* next;
    LT_Node_Data* data;
} LT_Node;

typedef struct _LT_Tree{
    LT_Node* root;
} LT_Tree;

#endif
