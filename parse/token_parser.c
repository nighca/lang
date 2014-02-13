#include <stdio.h>
#include <stdlib.h>

#include "token_parser.h"

void printToken(TokenState* token){
	printf("Type: %d, Val: '%s'\n", token->type, token->val);
}

int isTokenResolved(TokenState* token){
	int result = 0;
	int i = 0, length = sizeof(end)/sizeof(end[0]);
	for(; i < length; i++){
		if(token->type == end[i]){
			result = 1;
			break;
		}
	}

	return result;
}

int pushCharToToken(char* str, char c){
	//printf("PushChar: '%c'(%d) to '%s'\n", c, c, str);
	int i = 0;
	char* originStr = str;
	int max = MAX_TOKEN_LENGTH - 1;
	while(*str){
		str++;
		i++;
		if(i >= max){
			break;
		}
	}

	if(*str && i >= max){
		// Error: too long token
		printf("Error: too long token!!!\n");
		return 1;
	}else{
		*(str + 1) = '\0';
		*str = c;
		//printf("Pushed: '%s'\n", originStr);
		return 0;
	}	
}

int isCharNum(char c){
	return c >= '0' && c <= '9';
}

int isCharABC(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isCharIdentifierStart(char c){
	return isCharABC(c) || c == '_' || c == '$';
}

int isCharIdentifierPart(char c){
	return isCharIdentifierStart(c) || isCharNum(c);
}

int isCharOperator(char c){
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '&' || c == '|' || c == '!' || c == '=' || c == '^';
}

int isCharDivider(char c){
	return c == '\0' || c == '\n' || c == '\r' || c == ' ';
}

int changeTokenState(TokenState* s, char* code, int pos){
	char c = code[pos];
	//printf("Deal: char: '%c', token: ", c);
	//printToken(s);
	switch(s->type){
	case TOKEN_STATE_EMPTY:
		if(isCharIdentifierStart(c)){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_IDENTIFIER_START;
			return 1;
		}
		if(isCharNum(c)){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_DECIMAL_DIGITS;
			return 1;
		}
		if(c == '"'){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_STRING_HALF;
			return 1;
		}
		if(c == '('){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_LPT;
			return 1;
		}
		if(c == ')'){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_RPT;
			return 1;
		}
		if(isCharOperator(c)){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_OPERATOR;
			return 1;
		}
		if(isCharDivider(c)){
			return 1;
		}
		break;
	case TOKEN_STATE_IDENTIFIER:
		if(isCharIdentifierPart(c)){
			pushCharToToken(s->val, c);
			return 1;
		}
		break;
	case TOKEN_STATE_IDENTIFIER_START:
		if(isCharIdentifierPart(c)){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_IDENTIFIER;
			return 1;
		}else{
			s->type = TOKEN_STATE_IDENTIFIER;
		}
		break;
	case TOKEN_STATE_DECIMAL_DIGITS:
		if(isCharNum(c)){
			pushCharToToken(s->val, c);
			return 1;
		}
		break;
	case TOKEN_STATE_STRING_HALF:
		if(c == '\\'){
			pushCharToToken(s->val, code[pos+1]);
			return 2;
		}else if(c == '"'){
			pushCharToToken(s->val, c);
			s->type = TOKEN_STATE_STRING;
			return 1;
		}else if(c){
			pushCharToToken(s->val, c);
			return 1;
		}
		break;
	case TOKEN_STATE_STRING:
		break;
	case TOKEN_STATE_OPERATOR:
		break;
	case TOKEN_STATE_LPT:
		break;
	case TOKEN_STATE_RPT:
		break;
	}

	return 0;
}

TokenState* newToken(){
	TokenState* token = malloc(sizeof(TokenState));
	token->type = TOKEN_STATE_EMPTY;
	token->val[0] = '\0';
	return token;
}

int doParse(char* code, TokenState** results){
	int i = 0, j = 0;
	TokenState* token = newToken();
	while(code[i]){
		int step = changeTokenState(token, code, i);
		i += step;
		if(!step){
			if(isTokenResolved(token)){
				//printf("Resolved: ");
				//printToken(token);
				results[j++] = token;
				token = newToken();
			}else{
				// unknown char
				printf("Error: Unknown char caught: '%c'(%d) @%d in '%s' !!!\n", code[i], code[i], i, code);
				return 0;
			}
		}
	}

	if(isTokenResolved(token)){
		//printf("Resolved: ");
		//printToken(token);
		results[j++] = token;
	}

	return j;
}
