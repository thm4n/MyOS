#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../kernel.h"
#include "keymap.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define ENTER_KEY_CODE 0x1C

extern unsigned char keymap[128];

void kb_init();
void keyboard_handler_main();

#endif