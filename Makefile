run : build
	./build code/l
test : build
	./build code/s
build : parse/parser.c
	cc -std=c99 -o build util/util.c parse/token_parser.c parse/syntax_parser.c parse/parser.c execute/memory.c execute/Vtree.c execute/context.c lang/method.c execute/executor.c
clean :
	rm build
