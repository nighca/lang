#ifndef _TOKEN_PARSER_H
#define _TOKEN_PARSER_H

#define MAX_TOKEN_LENGTH 100

typedef enum {
	TOKEN_STATE_IDENTIFIER,
	TOKEN_STATE_IDENTIFIER_START,
	TOKEN_STATE_DECIMAL_DIGITS,

	TOKEN_STATE_LPT
	TOKEN_STATE_RPT
} TokenType;

TokenType end[] = {
	TOKEN_STATE_IDENTIFIER,
	TOKEN_STATE_LITERAL
};

struct {
	TokenType type;
	char* val;
} TokenState;

int pushCharToToken(char* str, char c){
	int i = 1;
	while(str++ && (i++) < MAX_TOKEN_LENGTH);

	if(*str && i >= MAX_TOKEN_LENGTH){
		// Error: too long token
		return 1;
	}else{
		*str = c;
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

int changeTokenState(TokenState* s, char c){
	switch(s->type){
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
		}
		break;
	case TOKEN_STATE_LITERAL:
		break;
	case TOKEN_STATE_NUMERICA_LITERAL:
		break;
	case TOKEN_STATE_DECIMAL_LITERAL:
		break;
	case TOKEN_STATE_DECIMAL_DIGITS:
		break;
	case TOKEN_STATE_DECIMAL_DIGIT:
		break;
	case TOKEN_STATE_LPT:
		break;
	case TOKEN_STATE_RPT:
		break;
	}
}

#endif
