#include "string.h"

int memcmp(const void* ptr1, const void* ptr2, size_t n) {
    const unsigned char* cptr1 = (const unsigned char*) ptr1;
	const unsigned char* cptr2 = (const unsigned char*) ptr2;
	for (size_t i = 0; i < n; i++) {
		if (cptr1[i] < cptr2[i])
			return -1;
		else if (cptr2[i] < cptr1[i])
			return 1;
	}
	return 0;
}

void* memcpy(void* __restrict dst, const void* __restrict src, size_t n) {
    unsigned char* cdst = (unsigned char*) dst;
	const unsigned char* csrc = (const unsigned char*) src;
	for (size_t i = 0; i < n; i++)
		cdst[i] = csrc[i];
	return dst;
}

void* memmove(void* dst, const void* src, size_t n) {
    unsigned char* cdst = (unsigned char*) dst;
	const unsigned char* csrc = (const unsigned char*) src;
	if (dst < src) {
		for (size_t i = 0; i < n; i++)
			cdst[i] = csrc[i];
	} else {
		for (size_t i = n; i != 0; i--)
			cdst[i-1] = csrc[i-1];
	}
	return dst;
}

void* memset(void* dst, int value, size_t n) {
    unsigned char* cdst = (unsigned char*) dst;
	for (size_t i = 0; i < n; i++)
		cdst[i] = (unsigned char) value;
	return dst;
}

size_t strlen(const char* str) {
    size_t len = 0;
	while (str[len++]);
	return len;
}

