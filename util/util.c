#include <stdio.h>
#include <stdlib.h>

#include "util.h"

void assert(int condition, const char* message){
    if(!condition){
        printf("%s\n", message);
        exit(1);
    }
}

int strEqual(char* s1, char* s2){
	int i = 0;
	for(; s1[i]; i++){
		if(s1[i] != s2[i]){
			return 0;
		}
	}

	return (s1[i] == s2[i]);
}

char* strCopy(char* from, char* to){
	int l;
	for(l = 0; from[l]; l++);

	if(!to){
		to = malloc(sizeof(char) * (l + 1));
		
		int i = 0;
		while(to[i] = from[i]) i++;
	}

	return to;
}

int parseNum(char* input, int ary){
	int n = 0;
	char c;

	while(c = *(input++)){
		n *= ary;
		n += (c - '0');
	}
	
	return n;
}

char* parseString(char* input){
	int l;
	for(l = 0; input[l]; l++);

	char* result = malloc(sizeof(char) * (l - 1));

	int i = 0;
	for(; i < l - 2; i++){
		result[i] = input[i+1];
	}

	result[i] = '\0';

	return result;
}