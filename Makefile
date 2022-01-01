# Binaries
MAIN            := main
DRA             := dra

# Compilers
GCC_MODERN		:= $(CROSS)gcc
GCC_272		    := ./bin/cc1
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := $(GCC_272)
LD              := $(CROSS)ld
CPP				:= cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections
CC_FLAGS        += -mips1 -mcpu=3000 -quiet -G0 -Wall -fno-builtin -mno-abicalls -fsigned-char -O2
CPP_FLAGS       := -Iinclude -undef -Wall -lang-c -fno-builtin -gstabs
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C

# Directories
ASM_DIR         := asm
SRC_DIR         := src
BUILD_DIR       := build
CONFIG_DIR      := config
TOOLS_DIR       := tools

# Files
MAIN_ASM_DIRS   := $(ASM_DIR)/$(MAIN) $(ASM_DIR)/$(MAIN)/psxsdk $(ASM_DIR)/$(MAIN)/data
MAIN_SRC_DIRS   := $(SRC_DIR)/$(MAIN) $(SRC_DIR)/$(MAIN)/psxsdk
MAIN_S_FILES    := $(foreach dir,$(MAIN_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(MAIN_ASM_DIRS),$(wildcard $(dir)/**/*.s))
MAIN_C_FILES    := $(foreach dir,$(MAIN_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(MAIN_SRC_DIRS),$(wildcard $(dir)/**/*.c))
MAIN_O_FILES    := $(foreach file,$(MAIN_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(MAIN_C_FILES),$(BUILD_DIR)/$(file).o)
MAIN_TARGET     := $(BUILD_DIR)/$(MAIN)

DRA_ASM_DIRS   := $(ASM_DIR)/$(DRA) $(ASM_DIR)/$(DRA)/data
DRA_SRC_DIRS   := $(SRC_DIR)/$(DRA)
DRA_S_FILES    := $(foreach dir,$(DRA_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(DRA_ASM_DIRS),$(wildcard $(dir)/**/*.s))
DRA_C_FILES    := $(foreach dir,$(DRA_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(DRA_SRC_DIRS),$(wildcard $(dir)/**/*.c))
DRA_O_FILES    := $(foreach file,$(DRA_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(DRA_C_FILES),$(BUILD_DIR)/$(file).o)
DRA_TARGET     := $(BUILD_DIR)/$(DRA)
DRABIN_TARGET  := $(BUILD_DIR)/DRA.BIN

# Tooling
PYTHON          := python3
SPLAT_DIR       := $(TOOLS_DIR)/n64splat
SPLAT           := $(PYTHON) $(SPLAT_DIR)/split.py

all: main dra
clean:
	rm -rf $(BUILD_DIR)

main: main_dirs $(MAIN_TARGET).exe
	sha1sum --check $(MAIN).sha
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(MAIN_TARGET).exe: $(MAIN_TARGET).elf
	$(OBJCOPY) --dump-section .header=$(MAIN_TARGET).header $<
	$(OBJCOPY) -O binary $< $(MAIN_TARGET).bin
	cat $(MAIN_TARGET).header $(MAIN_TARGET).bin > $@
$(MAIN_TARGET).elf: $(MAIN_O_FILES)
	$(LD) -o $@ \
	-Map $(MAIN_TARGET).map \
	-T $(MAIN).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(MAIN).txt \
	--no-check-sections \
	-nostdlib \
	-s

dra: dra_dirs $(DRABIN_TARGET)
	sha1sum --check $(DRA).sha
dra_dirs:
	$(foreach dir,$(DRA_ASM_DIRS) $(DRA_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(DRABIN_TARGET): $(DRA_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(DRA_TARGET).elf: $(DRA_O_FILES)
	$(LD) -o $@ \
	-Map $(DRA_TARGET).map \
	-T dra.ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(DRA).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(DRA).txt \
	--no-check-sections \
	-nostdlib \
	-s

extract: extract_main extract_dra
extract_main: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(MAIN).yaml
extract_dra: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(DRA).yaml

$(SPLAT_DIR):
	git submodule init $(SPLAT_DIR)
	git submodule update $(SPLAT_DIR)
	pip3 install -r $(SPLAT_DIR)/requirements.txt

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.s: %.c
	$(CPP) $(CPP_FLAGS) $< | $(CC) $(CC_FLAGS) -o $@

SHELL = /bin/bash -e -o pipefail

.PHONY: all, clean
.PHONY: main, main_dirs, dra, dra_dirs
.PHONY: extract, extract_main, extract_dra
