# Binaries
MAIN            := main
DRA             := dra
STMAD           := stmad
STNO3           := stno3

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

STMAD_ASM_DIRS   := $(ASM_DIR)/st/mad $(ASM_DIR)/st/mad/data
STMAD_SRC_DIRS   := $(SRC_DIR)/st/mad
STMAD_S_FILES    := $(foreach dir,$(STMAD_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STMAD_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STMAD_C_FILES    := $(foreach dir,$(STMAD_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STMAD_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STMAD_O_FILES    := $(foreach file,$(STMAD_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STMAD_C_FILES),$(BUILD_DIR)/$(file).o)
STMAD_TARGET     := $(BUILD_DIR)/$(STMAD)
STMADBIN_TARGET  := $(BUILD_DIR)/MAD.BIN

STNO3_ASM_DIRS   := $(ASM_DIR)/st/no3 $(ASM_DIR)/st/no3/data
STNO3_SRC_DIRS   := $(SRC_DIR)/st/no3
STNO3_S_FILES    := $(foreach dir,$(STNO3_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STNO3_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STNO3_C_FILES    := $(foreach dir,$(STNO3_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STNO3_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STNO3_O_FILES    := $(foreach file,$(STNO3_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STNO3_C_FILES),$(BUILD_DIR)/$(file).o)
STNO3_TARGET     := $(BUILD_DIR)/$(STNO3)
STNO3BIN_TARGET  := $(BUILD_DIR)/NO3.BIN

# Tooling
PYTHON          := python3
SPLAT_DIR       := $(TOOLS_DIR)/n64splat
SPLAT           := $(PYTHON) $(SPLAT_DIR)/split.py

all: main dra mad no3
	sha1sum --check slus00067.sha
clean:
	rm -rf $(BUILD_DIR)

main: main_dirs $(MAIN_TARGET).exe
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
dra_dirs:
	$(foreach dir,$(DRA_ASM_DIRS) $(DRA_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(DRABIN_TARGET): $(DRA_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(DRA_TARGET).elf: $(DRA_O_FILES)
	$(LD) -o $@ \
	-Map $(DRA_TARGET).map \
	-T $(DRA).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(DRA).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(DRA).txt \
	--no-check-sections \
	-nostdlib \
	-s

mad: mad_dirs $(STMADBIN_TARGET)
mad_dirs:
	$(foreach dir,$(STMAD_ASM_DIRS) $(STMAD_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STMADBIN_TARGET): $(STMAD_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STMAD_TARGET).elf: $(STMAD_O_FILES)
	$(LD) -o $@ \
	-Map $(STMAD_TARGET).map \
	-T $(STMAD).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STMAD).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STMAD).txt \
	--no-check-sections \
	-nostdlib \
	-s

no3: no3_dirs $(STNO3BIN_TARGET)
no3_dirs:
	$(foreach dir,$(STNO3_ASM_DIRS) $(STNO3_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STNO3BIN_TARGET): $(STNO3_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STNO3_TARGET).elf: $(STNO3_O_FILES)
	$(LD) -o $@ \
	-Map $(STNO3_TARGET).map \
	-T $(STNO3).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STNO3).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STNO3).txt \
	--no-check-sections \
	-nostdlib \
	-s

extract: extract_main extract_dra extract_mad extract_no3
extract_main: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(MAIN).yaml
extract_dra: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(DRA).yaml
extract_mad: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STMAD).txt > $(CONFIG_DIR)/generated.symbols.$(STMAD).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STMAD).yaml
extract_no3: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STNO3).txt > $(CONFIG_DIR)/generated.symbols.$(STNO3).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STNO3).yaml
$(CONFIG_DIR)/generated.symbols.%.txt:

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
.PHONY: main, main_dirs, dra, dra_dirs, mad, mad_dirs, no3, no3_dirs
.PHONY: extract, extract_main, extract_dra, extract_mad, extract_no3
