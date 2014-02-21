#ifndef _UTIL_H
#define _UTIL_H

void assert(int condition, const char* message){
    if(!condition){
        printf("%s\n", message);
        exit(1);
    }
}

#endif
