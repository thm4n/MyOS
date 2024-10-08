;;kernel.asm

;nasm directive - 32 bit
bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
global load_idt
global keyboard_handler

extern kmain	        ;kmain is defined in the c file
extern keyboard_handler_main

;%include 'kernel/general/portIO.asm'
%include 'src/kernel/general/load_idt.asm'
%include 'src/kernel/general/dev_handler.asm'

start:
  cli 			;block interrupts
  mov esp, stack_space	;set stack pointer
  call kmain
  hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space: