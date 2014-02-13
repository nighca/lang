#include <stdio.h>
#include <stdlib.h>

#include "../parse/parser.h"
#include "executor.h"

int main(int argc, const char * argv[]) {
	char code[1000] = "";
	gets(code);

	Tree* tree = parse(code);
	printNode(tree->root, 0);
}
