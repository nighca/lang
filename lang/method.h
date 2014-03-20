#ifndef _METHOD_H
#define _METHOD_H

char* nativeMthods = {
	"def",
	"lamda",
	"add",
	"minus",
	"multiply",
	"divide"
};

int def(Node** args, Node* result);

int lamda(Node** args, Node* result);

int add(Node** args, Node* result);

int minus(Node** args);

int multiply(Node** args);

int divide(Node** args);

#endif