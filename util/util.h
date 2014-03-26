#ifndef _UTIL_H
#define _UTIL_H

#define bool int
#define true 1
#define false 0

#define assert(condition, ...) \
if(!(condition)){ \
	printf("%s: %d: \n", __FILE__, __LINE__); \
	printf(__VA_ARGS__); \
	printf("\n"); \
	exit(1); \
}

//void assert(int condition, const char* message);

int strEqual(char* s1, char* s2);

char* strCopy(char* from, char* to);

char* strConcat(char* s1, char* s2);

int parseNum(char* input, int ary);

char* parseString(char* input);

void printTab(int num);

char* itos(int num, int ary);

int stoi(char* str, int ary);

#endif
