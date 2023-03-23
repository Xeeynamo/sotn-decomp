.SECONDEXPANSION:
.SECONDARY:

VERSION			?= us
MODULE_NAME		:= sotn-debugmode

# Directories
BIN_DIR         := ../../bin
ASM_DIR         := ../../asm
SRC_DIR         := ../../src
ASSETS_DIR      := ../../assets
INCLUDE_DIR     := ../../include
BUILD_DIR       := ../../build
DISK_DIR        := ../../$(BUILD_DIR)/$(VERSION)/disk
CONFIG_DIR      := ../../config
TOOLS_DIR       := ../../tools

# Compilers
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := $(BIN_DIR)/cc1-26
LD              := $(CROSS)ld
CPP				:= $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -I../../include -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
CC_FLAGS        += -mcpu=3000 -quiet -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fgnu-linker -mgas -msoft-float
CPP_FLAGS       += -I../../include -undef -Wall -lang-c -fno-builtin -gstabs
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C

all: build
build: $(BUILD_DIR)/$(MODULE_NAME).bin
clean:
	rm -f $(BUILD_DIR)/$(MODULE_NAME).*
	rm -rf $(BUILD_DIR)/tools/$(MODULE_NAME)
format:
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.c")
	clang-format -i $$(find $(INCLUDE_DIR)/ -type f -name "*.h")

$(BUILD_DIR)/$(MODULE_NAME).bin: $(BUILD_DIR)/$(MODULE_NAME).elf
	$(OBJCOPY) -O binary $< $@
	printf '\x00' | dd of=$@ bs=1 seek=40959 count=1 conv=notrunc

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/tools/%/debugmode.o $(BUILD_DIR)/tools/%/fontmanager.o $(BUILD_DIR)/tools/%/entity_spawn.o $(BUILD_DIR)/tools/%/sfx_player.o $(BUILD_DIR)/tools/%/collision_viewer.o $(BUILD_DIR)/tools/%/flag_checker.o $(BUILD_DIR)/tools/%/dra_800FD874.o
	$(LD) -o $@ \
	-Map $*.map \
	-T $*.ld \
	-T $(CONFIG_DIR)/symbols.$(VERSION).txt \
	--no-check-sections \
	-nostdlib \
	-s

$(BUILD_DIR)/tools/$(MODULE_NAME)/%.o: $(BUILD_DIR)/tools/$(MODULE_NAME)/%.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/tools/$(MODULE_NAME)/%.s: $(BUILD_DIR)/tools/$(MODULE_NAME)/%.c
	$(CC) $(CC_FLAGS) -o $@ $<
$(BUILD_DIR)/tools/$(MODULE_NAME)/%.c: %.c
	mkdir -p $(BUILD_DIR)/tools/$(MODULE_NAME)
	$(CPP) $(CPP_FLAGS) -o $@ $<
