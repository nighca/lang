#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "../parse/parser.h"
#include "memory.h"
#include "context.h"
#include "executor.h"

/*int main(int argc, const char * argv[]) {
	char code[1000] = "";
	gets(code);

	Tree* tree = parse(code);
	printNode(tree->root, 0);
}
*/

Context* global = newContext();
Context* contextStack[CALL_STACK_SIZE] = {global};
int curr = 0;

int calc(Node* expr){
	
};

int execute(char* code){
	return 0;
}