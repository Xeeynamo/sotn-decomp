# Binaries
MAIN            := main
DRA             := dra
STDRE           := stdre
STMAD           := stmad
STNO3           := stno3
STNP3           := stnp3
STST0           := stst0
STWRP           := stwrp
STRWRP          := strwrp

# Compilers
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := ./bin/cc1-26
LD              := $(CROSS)ld
CPP				:= $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1
CC_FLAGS        += -mips1 -mcpu=3000 -quiet -G0 -Wall -fno-builtin -mno-abicalls -fsigned-char -O2
CPP_FLAGS       += -Iinclude -undef -Wall -lang-c -fno-builtin -gstabs
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

STDRE_ASM_DIRS   := $(ASM_DIR)/st/dre $(ASM_DIR)/st/dre/data
STDRE_SRC_DIRS   := $(SRC_DIR)/st/dre
STDRE_S_FILES    := $(foreach dir,$(STDRE_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STDRE_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STDRE_C_FILES    := $(foreach dir,$(STDRE_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STDRE_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STDRE_O_FILES    := $(foreach file,$(STDRE_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STDRE_C_FILES),$(BUILD_DIR)/$(file).o)
STDRE_TARGET     := $(BUILD_DIR)/$(STDRE)
STDREBIN_TARGET  := $(BUILD_DIR)/DRE.BIN

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

STNP3_ASM_DIRS   := $(ASM_DIR)/st/np3 $(ASM_DIR)/st/np3/data
STNP3_SRC_DIRS   := $(SRC_DIR)/st/np3
STNP3_S_FILES    := $(foreach dir,$(STNP3_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STNP3_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STNP3_C_FILES    := $(foreach dir,$(STNP3_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STNP3_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STNP3_O_FILES    := $(foreach file,$(STNP3_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STNP3_C_FILES),$(BUILD_DIR)/$(file).o)
STNP3_TARGET     := $(BUILD_DIR)/$(STNP3)
STNP3BIN_TARGET  := $(BUILD_DIR)/NP3.BIN

STST0_ASM_DIRS   := $(ASM_DIR)/st/st0 $(ASM_DIR)/st/st0/data
STST0_SRC_DIRS   := $(SRC_DIR)/st/st0
STST0_S_FILES    := $(foreach dir,$(STST0_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STST0_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STST0_C_FILES    := $(foreach dir,$(STST0_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STST0_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STST0_O_FILES    := $(foreach file,$(STST0_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STST0_C_FILES),$(BUILD_DIR)/$(file).o)
STST0_TARGET     := $(BUILD_DIR)/$(STST0)
STST0BIN_TARGET  := $(BUILD_DIR)/ST0.BIN

STWRP_ASM_DIRS   := $(ASM_DIR)/st/wrp $(ASM_DIR)/st/wrp/data
STWRP_SRC_DIRS   := $(SRC_DIR)/st/wrp
STWRP_S_FILES    := $(foreach dir,$(STWRP_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STWRP_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STWRP_C_FILES    := $(foreach dir,$(STWRP_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STWRP_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STWRP_O_FILES    := $(foreach file,$(STWRP_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STWRP_C_FILES),$(BUILD_DIR)/$(file).o)
STWRP_TARGET     := $(BUILD_DIR)/$(STWRP)
STWRPBIN_TARGET  := $(BUILD_DIR)/WRP.BIN

STRWRP_ASM_DIRS  := $(ASM_DIR)/st/rwrp $(ASM_DIR)/st/rwrp/data
STRWRP_SRC_DIRS  := $(SRC_DIR)/st/rwrp
STRWRP_S_FILES   := $(foreach dir,$(STRWRP_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(STRWRP_ASM_DIRS),$(wildcard $(dir)/**/*.s))
STRWRP_C_FILES   := $(foreach dir,$(STRWRP_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(STRWRP_SRC_DIRS),$(wildcard $(dir)/**/*.c))
STRWRP_O_FILES   := $(foreach file,$(STRWRP_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(STRWRP_C_FILES),$(BUILD_DIR)/$(file).o)
STRWRP_TARGET    := $(BUILD_DIR)/$(STRWRP)
STRWRPBIN_TARGET := $(BUILD_DIR)/RWRP.BIN

# Tooling
PYTHON          := python3
SPLAT_DIR       := $(TOOLS_DIR)/n64splat
SPLAT           := $(PYTHON) $(SPLAT_DIR)/split.py

all: main dra dre mad no3 np3 st0 wrp rwrp
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

dre: dre_dirs $(STDREBIN_TARGET)
dre_dirs:
	$(foreach dir,$(STDRE_ASM_DIRS) $(STDRE_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STDREBIN_TARGET): $(STDRE_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STDRE_TARGET).elf: $(STDRE_O_FILES)
	$(LD) -o $@ \
	-Map $(STDRE_TARGET).map \
	-T $(STDRE).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STDRE).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STDRE).txt \
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

np3: np3_dirs $(STNP3BIN_TARGET)
np3_dirs:
	$(foreach dir,$(STNP3_ASM_DIRS) $(STNP3_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STNP3BIN_TARGET): $(STNP3_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STNP3_TARGET).elf: $(STNP3_O_FILES)
	$(LD) -o $@ \
	-Map $(STNP3_TARGET).map \
	-T $(STNP3).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STNP3).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STNP3).txt \
	--no-check-sections \
	-nostdlib \
	-s

st0: st0_dirs $(STST0BIN_TARGET)
st0_dirs:
	$(foreach dir,$(STST0_ASM_DIRS) $(STST0_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STST0BIN_TARGET): $(STST0_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STST0_TARGET).elf: $(STST0_O_FILES)
	$(LD) -o $@ \
	-Map $(STST0_TARGET).map \
	-T $(STST0).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STST0).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STST0).txt \
	--no-check-sections \
	-nostdlib \
	-s

wrp: wrp_dirs $(STWRPBIN_TARGET)
wrp_dirs:
	$(foreach dir,$(STWRP_ASM_DIRS) $(STWRP_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STWRPBIN_TARGET): $(STWRP_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STWRP_TARGET).elf: $(STWRP_O_FILES)
	$(LD) -o $@ \
	-Map $(STWRP_TARGET).map \
	-T $(STWRP).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STWRP).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STWRP).txt \
	--no-check-sections \
	-nostdlib \
	-s

rwrp: rwrp_dirs $(STRWRPBIN_TARGET)
rwrp_dirs:
	$(foreach dir,$(STRWRP_ASM_DIRS) $(STRWRP_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(STRWRPBIN_TARGET): $(STRWRP_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(STRWRP_TARGET).elf: $(STRWRP_O_FILES)
	$(LD) -o $@ \
	-Map $(STRWRP_TARGET).map \
	-T $(STRWRP).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(STRWRP).txt \
	-T $(CONFIG_DIR)/undefined_funcs_auto.$(STRWRP).txt \
	--no-check-sections \
	-nostdlib \
	-s

extract: extract_main extract_dra extract_dre extract_mad extract_no3 extract_np3 extract_st0 extract_wrp extract_rwrp
extract_main: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(MAIN).yaml
extract_dra: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(DRA).yaml
extract_dre: $(SPLAT_DIR)
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STDRE).yaml
extract_mad: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STMAD).txt > $(CONFIG_DIR)/generated.symbols.$(STMAD).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STMAD).yaml
extract_no3: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STNO3).txt > $(CONFIG_DIR)/generated.symbols.$(STNO3).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STNO3).yaml
extract_np3: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STNP3).txt > $(CONFIG_DIR)/generated.symbols.$(STNP3).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STNP3).yaml
extract_st0: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STST0).txt > $(CONFIG_DIR)/generated.symbols.$(STST0).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STST0).yaml
extract_wrp: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STWRP).txt > $(CONFIG_DIR)/generated.symbols.$(STWRP).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STWRP).yaml
extract_rwrp: $(SPLAT_DIR)
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.$(STRWRP).txt > $(CONFIG_DIR)/generated.symbols.$(STRWRP).txt
	$(SPLAT) --basedir . $(CONFIG_DIR)/splat.$(STRWRP).yaml
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
.PHONY: main, main_dirs, dra, dra_dirs, dre, dre_dirs, mad, mad_dirs, no3, no3_dirs, np3, np3_dirs, st0, st0_dirs, wrp, wrp_dirs, rwrp, rwrp_dirs
.PHONY: extract, extract_main, extract_dra, extract_dre, extract_mad, extract_no3, extract_np3, extract_st0, extract_wrp, extract_rwrp
