BIN_DIR := ./bin
SRC_DIR := ./src

ASM_SRC    := $(shell find ./src -name "kstart.asm")
C_SRC    := $(shell find ./src -name "*.c")

ASM_OBJ   := $(patsubst $(SRC_DIR)/%.asm,$(BIN_DIR)/%.o,$(ASM_SRC))
C_OBJ   := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(C_SRC))

CROSS_PATH  := /opt/cross/bin
TARGET_ARCH := i386-elf

CC = ${CROSS_PATH}/${TARGET_ARCH}-gcc
LD := ${CROSS_PATH}/${TARGET_ARCH}-ld

CC_INC_FLAGS = -I./src -I./src/libc -I./src/std

CCFLAGS := -m32 -c -ffreestanding -fno-stack-protector $(CC_INC_FLAGS)
LDFLAGS := -m elf_i386 -T $(shell find . -name "link.ld")

TARGET := $(BIN_DIR)/kstart.bin

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	${CC} ${CCFLAGS} $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

test:
	@echo ${C_SRC}
	@echo ${C_OBJ}

$(BIN_DIR)/%.bin: ${C_OBJ} $(ASM_OBJ)
	${LD} ${LDFLAGS} $^ -o $@

rebuild: clean $(TARGET)

build: $(TARGET)
	@echo "created $<"

rerun: clean $(TARGET)

run: $(TARGET)
	qemu-system-i386 -kernel $<

clean:
	rm -rf ./bin/*
	rm -f $(TARGET)
