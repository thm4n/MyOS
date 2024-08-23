#include "keyboard.h"

#include "keymap.h"

void kb_init() {
	port_byte_out(0x21 , 0xFD);
}

void keyboard_handler_main() {
	unsigned char status;
	char keycode;
	char* vidptr = VGA_MEM;

	port_byte_out(0x20, 0x20);

	status = port_byte_in(KEYBOARD_STATUS_PORT);

	if (status & 0x01) {
		keycode = port_byte_in(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

		print_char(keymap[(unsigned char) keycode], -1, -1, VGA_ATTR(BLACK, LGREY));
	}
}
