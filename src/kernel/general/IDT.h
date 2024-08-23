#ifndef _IDT_H_
#define _IDT_H_

#include "../drivers/keyboard.h"

#define IDT_SIZE 256

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

extern void load_idt(unsigned long *idt_ptr);

void idt_init(void);

#endif