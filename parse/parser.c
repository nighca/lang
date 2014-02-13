#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "token_parser.h"
#include "syntax_parser.h"
#include "parser.h"

int resolve(TokenState** tokens, int left, Node* node){
	if(!left){
		return 0;
	}

	TokenState* token;
	TokenState** originTokens = tokens;
	int originLeft = left;

	token = *tokens;

	switch(token->type){
	case TOKEN_STATE_LPT:
		{
			Node* n = newNode();
			tokens++;
			left--;
			int offset = 1;
			int step;
			while(step = resolve(tokens, left, n)){
				addChild(node, n);
				n = newNode();
				tokens += step;
				left -= step;
				offset += step;
			}
			token = *tokens;
			if(token->type == TOKEN_STATE_RPT){
				return offset + 1;
			}else{
				// missing ')'
				printf("Error: Missing ')'\n");
				return 0;
			}
		}
		break;
	case TOKEN_STATE_IDENTIFIER:
		node->val->type = VALUE_TYPE_VAR; 
		node->val->data = token->val;
		return 1;
	case TOKEN_STATE_DECIMAL_DIGITS:
		node->val->type = VALUE_TYPE_NUM; 
		node->val->data = token->val;
		return 1;
	case TOKEN_STATE_STRING:
		node->val->type = VALUE_TYPE_STRING; 
		node->val->data = token->val;
		return 1;
	case TOKEN_STATE_OPERATOR:
		node->val->type = VALUE_TYPE_LAMDA; 
		node->val->data = token->val;
		return 1;
	}
	return 0;
}

Tree* parse(char* code) {
	TokenState* result[MAX_TOKEN_NUM];
	int num;
	Tree* tree = newTree();

	if(num = doParse(code, result)){
		int resolved = resolve(result, num, tree->root);

		if(!resolved){
			// no node resolved
			printf("Error: no node resolved!!!\n");
		}

		if(resolved < num){
			// extra token
			printf("Error: extra token!!!\n");
		}
	}

	return tree;
}

/*
int main(int argc, const char * argv[]) {
	char code[1000] = "";
	gets(code);

	Tree* tree = parse(code);
	printNode(tree->root, 0);
}
*/