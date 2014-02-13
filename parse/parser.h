#ifndef _PARSER_H
#define _PARSER_H

#define MAX_TOKEN_NUM 100

int resolve(TokenState** tokens, int left, Node* node);

Tree* parse(char* code);

#endif
