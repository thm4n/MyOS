BIN_DIR := ./bin
SRC_DIR := ./src

ASM_SRC    := $(shell find . -name "kernel.asm")
C_SRC    := $(shell find . -name "*.c")

ASM_OBJ   := $(ASM_SRC:.asm=.o)
C_OBJ     := $(C_SRC:.c=.o)

ASM_OBJ_FILES := $(patsubst $(SRC_DIR)/%.asm,$(BIN_DIR)/%.o,$(ASM_OBJ))
C_OBJ_FILES   := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(C_OBJ))

CROSS_PATH  := $(shell echo ~/opt/cross/bin/)
TARGET_ARCH := i386-elf

CC := ${CROSS_PATH}/${TARGET_ARCH}-gcc
LD := ${CROSS_PATH}/${TARGET_ARCH}-ld

CCFLAGS := -m32 -c -ffreestanding -fno-stack-protector -I./std
LDFLAGS := -m elf_i386 -T $(shell find . -name "link.ld")

check:
	echo ${CROSS_PATH}

%.o: %.c
	${CC} ${CCFLAGS} $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@

kernel.bin: ${OBJ}
	${LD} ${LDFLAGS} $^ -o $@

rebuild: clean kernel.bin

build: kernel.bin

rerun: clean kernel.bin

run: kernel.bin
	qemu-system-i386 -kernel $<

clean:
	rm -f ${shell find . -name "*.o"}
	rm -f kernel.bin
