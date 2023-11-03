#include "string.h"

void* memcpy(void* dest, void* src, unsigned int n) {
    char* cdest = (char*)dest;
    char* csrc = (char*)src;
    for(int i = 0; i < n; i++)
        cdest[i] = csrc[i];
    return dest;
}

