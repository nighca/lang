#ifndef _PARSER_H
#define _PARSER_H

void assert(int condition, const char* message){
    if(!condition){
        printf("%s\n", message);
        exit(1);
    }
}

#endif
