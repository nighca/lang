#include <stdio.h>
#include <stdlib.h>

#include "token_parser.h"

#define MAX_TOKEN_NUM 100

int main(int argc, const char * argv[]) {
	TokenState* result[MAX_TOKEN_NUM];
	char code[1000] = "";
	gets(code);

	int num;
	if(num = doParse(code, result)){
	//	for(int i = 0; i < num; i++){
	//		TokenState* token = result[i];
	//	}
	}
	printf("Result: Token num: %d\n", num);
}
