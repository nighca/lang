#ifndef _SYNTAX_TREE_H
#define _SYNTAX_TREE_H

#define TRUE 1
#define FALSE 0

typedef int Bool;

typedef enum {
    CALC,
    ARGS,
    EXPRESSION,
    TOKEN
} ST_Node_Type;

typedef struct _ST_Node_Data{
    ST_Node_Type type;
    
} ST_Node_Data;

typedef struct _ST_Node{
    _ST_Node* child;
    _ST_Node* next;
    ST_Node_Data* data;
} ST_Node;

typedef struct _ST_Tree{
    ST_Node* root;
} ST_Tree;

#endif
