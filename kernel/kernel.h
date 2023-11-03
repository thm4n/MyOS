#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "drivers/screen.h"
#include "general/ports.h"
#include "../std/stdlib.h"
#include "../std/string.h"

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern void load_idt(unsigned long *idt_ptr);

#endif