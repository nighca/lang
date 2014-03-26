#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/*void assert(int condition, const char* message){
    if(!condition){
        printf("%s\n", message);
        exit(1);
    }
}*/

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

char* strConcat(char* s1, char* s2){
	int l1, l2;
	for(l1 = 0; s1[l1]; l1++);
	for(l2 = 0; s2[l2]; l2++);

	char* ret = malloc(sizeof(char) * (l1 + l2 + 1));
		
	for(int i = 0; i < l1; i++) ret[i] = s1[i];
	for(int i = 0; i < l2; i++) ret[l1 + i] = s2[i];

	return ret;
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

void printTab(int num){
	for(int i = 0; i < num; i++){
		printf("\t");
	}
}

char ARY_CODES[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char* itos(int num, int ary){
	assert(ary > 1 && ary <= 16, "Error: invalid ary: %d!", ary);

	int l = 1;
	int n = num;
	while(n >= ary){
		l++;
		n /= ary;
	}

	char* s = malloc(sizeof(char) * (l + 1));
	s[l--] = '\0';
	for(; l >= 0; l--){
		s[l] = ARY_CODES[num % ary];
		num /= ary;
	}

	return s;
}

int stoi(char* str, int ary){
	assert(ary > 1 && ary <= 16, "Error: invalid ary: %d!", ary);

	int n = 0;
	char c;

	while(c = *(str++)){
		if(c >= '0' && c <= '9'){
			n *= ary;
			n += (c - '0');
		}
		if(c >= 'a' && c <= 'f'){
			n *= ary;
			n += (c - 'a' + 10);
		}
	}
	
	return n;
}
