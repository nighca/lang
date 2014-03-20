run : build
	cat code/l | ./build
test : build
	cat code/s | ./build
build : parse/parser.c
	cc -std=c99 -o build util/util.c parse/token_parser.c parse/syntax_parser.c parse/parser.c execute/executor.c
clean :
	rm build
