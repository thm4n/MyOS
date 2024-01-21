CSRC = $(shell find . | grep -F .c)
SSRC = $(shell find . | grep -F kernel.asm)
OBJ = $(SSRC:.asm=.o) $(CSRC:.c=.o)

CROSS_PATH = $(shell echo ~/opt/cross/bin/)
TARGET = i386-elf

CC = ${CROSS_PATH}/${TARGET}-gcc
LD = ${CROSS_PATH}/${TARGET}-ld

CCFLAGS = -nostdlib -lk -lgcc -m32 -c -ffreestanding -fno-stack-protector -I./ -I./libc/include/
LDFLAGS = -nostdlib -lk -lgcc -m elf_i386 -T $(shell find . | grep -F link.ld)

check:
	echo ${CROSS_PATH}

%.o: %.c
	${CC} ${CCFLAGS} $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@

kernel.bin: ${OBJ}
	${LD} ${LDFLAGS} $^ -o $@

run: kernel.bin
	qemu-system-i386 -kernel $<

clean:
	rm -f ${shell find . | grep -F .o}
	rm -f kernel.bin
