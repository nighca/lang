run : build
	./build
build : parse/parser.c
	cc -std=c99 -o build parse/parser.c
clean :
	rm build
