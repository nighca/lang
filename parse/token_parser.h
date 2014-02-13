#ifndef _TOKEN_PARSER_H
#define _TOKEN_PARSER_H

#define MAX_TOKEN_LENGTH 100
#define MAX_TOKEN_NUM 100

typedef enum {
	TOKEN_STATE_EMPTY,
	TOKEN_STATE_IDENTIFIER,
	TOKEN_STATE_IDENTIFIER_START,
	TOKEN_STATE_DECIMAL_DIGITS,
	TOKEN_STATE_STRING_HALF,
	TOKEN_STATE_STRING,
	TOKEN_STATE_OPERATOR,

	TOKEN_STATE_LPT,
	TOKEN_STATE_RPT
} TokenType;

TokenType end[] = {
	TOKEN_STATE_IDENTIFIER,
	TOKEN_STATE_DECIMAL_DIGITS,
	TOKEN_STATE_STRING,
	TOKEN_STATE_OPERATOR,
	TOKEN_STATE_LPT,
	TOKEN_STATE_RPT
};

typedef struct {
	TokenType type;
	char val[MAX_TOKEN_LENGTH];
} TokenState;

void printToken(TokenState* token);

int isTokenResolved(TokenState* token);

int pushCharToToken(char* str, char c);

int isCharNum(char c);

int isCharABC(char c);

int isCharIdentifierStart(char c);

int isCharIdentifierPart(char c);

int isCharOperator(char c);

int isCharDivider(char c);

int changeTokenState(TokenState* s, char* code, int pos);

TokenState* newToken();

int doParse(char* code, TokenState** results);

#endif
