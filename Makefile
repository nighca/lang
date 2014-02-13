run : build
	cat code/l | ./build
test : build
	cat code/s | ./build
build : parse/parser.c
	cc -std=c99 -o build parse/parser.c
clean :
	rm build
