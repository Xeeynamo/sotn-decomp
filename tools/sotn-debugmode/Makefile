.SECONDEXPANSION:
.SECONDARY:

VERSION			?= us
MODULE_NAME		:= sotn-debugmode

# Directories
INCLUDE_DIR     := ../../include
BUILD_DIR       := ../../build
CONFIG_DIR      := ../../config

# Compilers
CROSS           := mipsel-linux-gnu-
CC				:= $(CROSS)gcc
LD              := $(CROSS)ld
CPP				:= $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
CC_FLAGS        += -c -march=r3000 -mtune=r3000 -EL -G0 -O0 -g -funsigned-char -w -mno-abicalls
CPP_FLAGS       += -I$(INCLUDE_DIR) -undef
CPP_FLAGS       += -D_internal_version_$(VERSION) -Dmips -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C

all: build
build: $(BUILD_DIR)/$(MODULE_NAME).bin
clean:
	rm -f $(BUILD_DIR)/$(MODULE_NAME).*
	rm -rf $(BUILD_DIR)/tools/$(MODULE_NAME)
format:
	clang-format -i $$(find . -type f -name "*.c")
	clang-format -i $$(find . -type f -name "*.h")

$(BUILD_DIR)/$(MODULE_NAME).bin: $(BUILD_DIR)/$(MODULE_NAME).elf
	$(OBJCOPY) -O binary $< $@
	printf '\x00' | dd of=$@ bs=1 seek=40959 count=1 conv=notrunc

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/tools/%/header.o $(BUILD_DIR)/tools/%/debugmode.o $(BUILD_DIR)/tools/%/fontmanager.o $(BUILD_DIR)/tools/%/entity_spawn.o $(BUILD_DIR)/tools/%/sfx_player.o $(BUILD_DIR)/tools/%/collision_viewer.o $(BUILD_DIR)/tools/%/flag_checker.o $(BUILD_DIR)/tools/%/dra_800FD874.o $(BUILD_DIR)/tools/%/stage_select.o
	$(LD) -o $@ -Map $*.map -T $*.ld -T $(CONFIG_DIR)/symbols.$(VERSION).txt \$^

$(BUILD_DIR)/tools/$(MODULE_NAME)/%.o: $(BUILD_DIR)/tools/$(MODULE_NAME)/%.c
	$(CC) $(CC_FLAGS) -o $@ $<
$(BUILD_DIR)/tools/$(MODULE_NAME)/%.c: %.c
	mkdir -p $(BUILD_DIR)/tools/$(MODULE_NAME)
	$(CPP) $(CPP_FLAGS) -o $@ $<
