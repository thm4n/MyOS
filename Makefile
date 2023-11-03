CSRC = $(shell find . | grep -F .c)
SSRC = $(shell find . | grep -F kernel.asm)
OBJ = $(SSRC:.asm=.o) $(CSRC:.c=.o)

CC = gcc
LD = ld

CCFLAGS = -m32 -c -ffreestanding -fno-stack-protector
LDFLAGS = -m elf_i386 -T $(shell find . | grep -F link.ld)

check:
	echo ${CSRC}

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
