# compilers & parameters

BIN_DIR := bin

TARGET_NAME := ritz.bin

TARGET_CPP := cpp
TARGET_AS := nasm -f elf32
TARGET_ASFLAGS := -i$(CURDIR)/src/include/
TARGET_CC := gcc -m32
TARGET_CFLAGS = -fno-PIC -nodefaultlibs -nostdlib -fno-builtin -Isrc/include
TARGET_LD := ld -m elf_i386 -no-PIE

QEMU ?= qemu-system-x86_64

# targets

TARGET_FILE := $(BIN_DIR)/$(TARGET_NAME)

SRC_DIRS := src/boot src/graphics src/kernel src/rlibc src/shell
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
O_FILES := $(foreach file,$(C_FILES),$(BIN_DIR)/$(file).o) \
    $(foreach file,$(S_FILES),$(BIN_DIR)/$(file).o)

$(BIN_DIR)/src/shell/kmode.c.o: TARGET_CFLAGS += -Wno-incompatible-pointer-types

# create all directories needed for build
ALL_DIRS := $(BIN_DIR) $(addprefix $(BIN_DIR)/,$(SRC_DIRS))
$(shell mkdir -p $(ALL_DIRS))

# compilation directives

$(BIN_DIR)/%.c.o: %.c
	$(TARGET_CC) -c $(TARGET_CFLAGS)  -o $@ $<

$(BIN_DIR)/%.s.o: %.s
	$(TARGET_AS) $(TARGET_ASFLAGS) -o $@ $<

$(BIN_DIR)/link.ld: link.ld
	$(TARGET_CPP) -P -DBIN_DIR=$(BIN_DIR) -o $@ $<

$(TARGET_FILE): $(O_FILES) $(BIN_DIR)/link.ld
	$(TARGET_LD) -Map=$(TARGET_FILE).map -T $(BIN_DIR)/link.ld -o $@ $(O_FILES)

ritz: $(TARGET_FILE)

clean:
	$(RM) -r $(BIN_DIR)

test: ritz
	$(QEMU) -fda $(TARGET_FILE) -cpu pentium -soundhw pcspk

.PHONY: clean test
.DEFAULT_GOAL := ritz
