#include "kernel.h"

void kmain(void) {
	clear_screen();

	kprint("i love mustaches\n", VGA_ATTR(BLACK, LGREY));
	kprint("i very much do love dogs as well!", VGA_ATTR(BLACK, LGREY));

	idt_init();
	kb_init();

	while(1);
}