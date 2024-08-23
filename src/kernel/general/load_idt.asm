;;load_idt.asm

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret
    