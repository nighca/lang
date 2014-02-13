#include <stdio.h>
#include <stdlib.h>

#include "../util/util.h"
#include "../parse/token_parser.h"
#include "../parse/syntax_parser.h"
#include "../parse/parser.h"
#include "executor.h"

int main(int argc, const char * argv[]) {
	char code[1000] = "";
	gets(code);

	Tree* tree = parse(code);
	printNode(tree->root, 0);
}
