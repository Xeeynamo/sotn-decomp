.SECONDEXPANSION:
.SECONDARY:

# Binaries
MAIN            := main
DRA             := dra

# Compilers
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := ./bin/cc1-26
LD              := $(CROSS)ld
CPP				:= $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1
CC_FLAGS        += -mcpu=3000 -quiet -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fgnu-linker -mgas -msoft-float
CPP_FLAGS       += -Iinclude -undef -Wall -lang-c -fno-builtin -gstabs
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C

# Directories
ASM_DIR         := asm
SRC_DIR         := src
ASSETS_DIR      := assets
INCLUDE_DIR     := include
BUILD_DIR       := build
DISK_DIR        := $(BUILD_DIR)/disk
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

# Tooling
PYTHON          := python3
SPLAT_DIR       := $(TOOLS_DIR)/n64splat
SPLAT_APP       := $(SPLAT_DIR)/split.py
SPLAT           := $(PYTHON) $(SPLAT_APP)
ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
ASMDIFFER_APP   := $(ASMDIFFER_DIR)/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2CTX           := $(PYTHON) $(M2CTX_APP)
M2C_DIR         := $(TOOLS_DIR)/m2c
M2C_APP         := $(M2C_DIR)/m2c.py
M2C             := $(PYTHON) $(M2C_APP)
M2C_ARGS		:= -P 4
GO				:= $(TOOLS_DIR)/go/bin/go
GOPATH			:= $(HOME)/go
ASPATCH			:= $(GOPATH)/bin/aspatch
SOTNDISK		:= $(GOPATH)/bin/sotn-disk

define list_src_files
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(SRC_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**.bin))
endef

define list_o_files
	$(foreach file,$(call list_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

define link
	$(LD) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(1).ld \
		-T $(CONFIG_DIR)/symbols.txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(1).txt \
		--no-check-sections \
		-nostdlib \
		-s
endef

all: build check
build: main dra ric cen dre mad no3 np3 nz0 sel st0 wrp rwrp
clean:
	git clean -fdx asm/
	git clean -fdx $(BUILD_DIR)
	git clean -fdx config/
	git clean -fx
format:
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.c")
	clang-format -i $$(find $(INCLUDE_DIR)/ -type f -name "*.h")
check:
	sha1sum --check slus00067.sha
expected: check
	rm -rf expected/build
	cp -r build expected/

main: main_dirs $(MAIN_TARGET).exe
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(MAIN_TARGET).exe: $(MAIN_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(MAIN_TARGET).elf: $(MAIN_O_FILES)
	$(LD) -o $@ \
	-Map $(MAIN_TARGET).map \
	-T $(MAIN).ld \
	-T $(CONFIG_DIR)/symbols.txt \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(MAIN).txt \
	--no-check-sections \
	-nostdlib \
	-s

dra: dra_dirs $(BUILD_DIR)/DRA.BIN
$(BUILD_DIR)/DRA.BIN: $(BUILD_DIR)/$(DRA).elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/$(DRA).elf: $(call list_o_files,dra)
	$(call link,dra,$@)

ric: ric_dirs $(BUILD_DIR)/RIC.BIN
$(BUILD_DIR)/RIC.BIN: $(BUILD_DIR)/ric.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/ric.elf: $(call list_o_files,ric)
	$(call link,ric,$@)

cen: stcen_dirs $(BUILD_DIR)/CEN.BIN
$(BUILD_DIR)/CEN.BIN: $(BUILD_DIR)/stcen.elf
	$(OBJCOPY) -O binary $< $@

dre: stdre_dirs $(BUILD_DIR)/DRE.BIN
$(BUILD_DIR)/DRE.BIN: $(BUILD_DIR)/stdre.elf
	$(OBJCOPY) -O binary $< $@

mad: stmad_dirs $(BUILD_DIR)/MAD.BIN
$(BUILD_DIR)/MAD.BIN: $(BUILD_DIR)/stmad.elf
	$(OBJCOPY) -O binary $< $@

no3: stno3_dirs $(BUILD_DIR)/NO3.BIN
$(BUILD_DIR)/NO3.BIN: $(BUILD_DIR)/stno3.elf
	$(OBJCOPY) -O binary $< $@

np3: stnp3_dirs $(BUILD_DIR)/NP3.BIN
$(BUILD_DIR)/NP3.BIN: $(BUILD_DIR)/stnp3.elf
	$(OBJCOPY) -O binary $< $@

nz0: stnz0_dirs $(BUILD_DIR)/NZ0.BIN
$(BUILD_DIR)/NZ0.BIN: $(BUILD_DIR)/stnz0.elf
	$(OBJCOPY) -O binary $< $@

sel: stsel_dirs $(BUILD_DIR)/SEL.BIN
$(BUILD_DIR)/SEL.BIN: $(BUILD_DIR)/stsel.elf
	$(OBJCOPY) -O binary $< $@

st0: stst0_dirs $(BUILD_DIR)/ST0.BIN
$(BUILD_DIR)/ST0.BIN: $(BUILD_DIR)/stst0.elf
	$(OBJCOPY) -O binary $< $@

wrp: stwrp_dirs $(BUILD_DIR)/WRP.BIN
$(BUILD_DIR)/WRP.BIN: $(BUILD_DIR)/stwrp.elf
	$(OBJCOPY) -O binary $< $@

rwrp: strwrp_dirs $(BUILD_DIR)/RWRP.BIN
$(BUILD_DIR)/RWRP.BIN: $(BUILD_DIR)/strwrp.elf
	$(OBJCOPY) -O binary $< $@

mad_fix: stmad_dirs mad_patch $(BUILD_DIR)/MAD.BIN
MAD_PATCHES = \
	-e "s/D_8003BEE8/D_8003BEEC/g" -e "s/0x8003BEE8/0x8003BEEC/g" \
	-e "s/D_8003BF08/D_8003BF7C/g" -e "s/0x8003BF08/0x8003BF7C/g" \
	-e "s/D_8003C6B0/g_api.FreePolygons/g" -e "s/0x8003C6B0/0x8003C7B4/g" \
	-e "s/D_8003C6B8/g_api.CheckCollision/g" -e "s/0x8003C6B8/0x8003C7BC/g" \
	-e "s/D_8003C6D8/g_api.PlaySfx/g" -e "s/0x8003C6D8/0x8003c7dc/g" \
	-e "s/D_8003C704/D_800A8900/g" -e "s/0x8003C704/0x8003C808/g" \
	-e "s/D_8003C724/D_8003C828/g" -e "s/0x8003C724/0x8003C828/g" \
	-e "s/D_8003C744/func_800FE044/g" -e "s/0x8003C744/0x8003C848/g" \
	-e "s/g_pfnInitRoomEntities/D_8003C8C4/g" -e "s/0x8003c780/0x8003C8C4/g" \
	-e "s/D_8006C26C/g_CurrentEntity/g" -e "s/0x8006C26C/0x8006C3B8/g" \
	-e "s/D_80072B34/g_CurrentRoomTileLayout/g" -e "s/0x80072B34/0x80073084/g" \
	-e "s/D_80072E8A/D_800733DA/g" -e "s/0x80072E8A/0x800733DA/g" \
	-e "s/D_80072E8E/D_800733DE/g" -e "s/0x80072E8E/0x800733DE/g" \
	-e "s/D_80072E88/D_800733D8/g" -e "s/0x80072E88/0x800733D8/g" \
	-e "s/D_80072EC2/D_80073412/g" -e "s/0x80072EC2/0x80073412/g" \
	-e "s/D_80072ED0/D_80073420/g" -e "s/0x80072ED0/0x80073420/g" \
	-e "s/D_80072F40/D_80073490/g" -e "s/0x80072F40/0x80073490/g" \
	-e "s/D_80072F44/D_80073494/g" -e "s/0x80072F44/0x80073494/g" \
	-e "s/D_800751C8/D_80075718/g" -e "s/0x800751C8/0x80075718/g" \
	-e "s/D_8007A408/D_8007A958/g" -e "s/0x8007A408/0x8007A958/g" \
	-e "s/D_8007BB88/D_8007C0D8/g" -e "s/0x8007BB88/0x8007C0D8/g" \
	-e "s/D_8007D308/D_8007D858/g" -e "s/0x8007D308/0x8007D858/g" \
	-e "s/D_8007E9CC/D_8007EF1C/g" -e "s/0x8007E9CC/0x8007EF1C/g" \
	-e "s/D_80086A9C/D_80086FEC/g" -e "s/0x80086A9C/0x80086FEC/g" \
	-e "s/D_80096EA8/D_800973F8/g" -e "s/0x80096EA8/0x800973F8/g" \
	-e "s/D_80096EB8/g_zEntityCenter/g" -e "s/0x80096EB8/0x80097408/g" \
	-e "s/D_80096EC0/D_80097410/g" -e "s/0x80096EC0/0x80097410/g" \
	-e "s/D_80096EC4/D_80097414/g" -e "s/0x80096EC4/0x80097414/g" \
	-e "s/D_80096ED8/g_entityDestroyed/g" \ -e "s/D_8009769C/g_playerGold/g" \
	-e "s/D_80097364/g_randomNext/g" -e "s/0x80097364/0x800978b8/g" \
	-e "s/D_800973B8/D_8009790C/g" -e "s/0x800973B8/0x8009790C/g" \
	-e "s/D_8009741B/D_8009796F/g" -e "s/0x8009741B/0x8009796F/g" \
	-e "s/D_8009741F/D_80097973/g" -e "s/0x8009741F/0x80097973/g" \
	-e "s/D_80072B3E/D_8007308E/g" -e "s/0x80072B3E/0x8007308E/g" \
	-e "s/D_80072B42/D_80073092/g" -e "s/0x80072B42/0x80073092/g" \
	-e "s/D_80072B58/g_CurrentRoomVSize/g" -e "s/0x80072B58/0x800730a8/g" \
	-e "s/D_80075D88/D_800762D8/g" -e "s/0x80075D88/0x800762D8/g" \
	-e "s/D_8007EA88/D_8007EFD8/g" -e "s/0x8007EA88/0x8007EFD8/g" \
	-e "s/D_80096EAC/D_800973FC/g" -e "s/0x80096EAC/0x800973FC/g" \
	-e "s/D_8009741A/D_8009796E/g" -e "s/0x8009741A/0x8009796E/g" \
	-e "s/D_800976A0/g_killCount/g" -e "s/0x800976A0/0x80097BF4/g"
mad_patch:
	find config -type f -name "*stmad.txt" -print0 | xargs -0 sed -i $(MAD_PATCHES)
	find asm/st/mad -type f -name "*.s" -print0 | xargs -0 sed -i $(MAD_PATCHES)
	find src/st/mad -type f -name "*.c" -print0 | xargs -0 sed -i $(MAD_PATCHES)

st%_dirs:
	$(foreach dir,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/$$*)
	$(call link,st$*,$@)

extract: extract_main extract_dra extract_ric extract_stcen extract_stdre extract_stmad extract_stno3 extract_stnp3 extract_stnz0 extract_stsel extract_stst0 extract_stwrp extract_strwrp
extract_main: require-tools
	$(SPLAT) $(CONFIG_DIR)/splat.$(MAIN).yaml
extract_dra: require-tools
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.dra.txt > $(CONFIG_DIR)/generated.symbols.dra.txt
	$(SPLAT) $(CONFIG_DIR)/splat.$(DRA).yaml
extract_ric: require-tools
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.ric.txt > $(CONFIG_DIR)/generated.symbols.ric.txt
	$(SPLAT) $(CONFIG_DIR)/splat.ric.yaml
extract_st%: require-tools
	cat $(CONFIG_DIR)/symbols.txt $(CONFIG_DIR)/symbols.st$*.txt > $(CONFIG_DIR)/generated.symbols.st$*.txt
	$(SPLAT) $(CONFIG_DIR)/splat.st$*.yaml
$(CONFIG_DIR)/generated.symbols.%.txt:

context:
	$(M2CTX) $(SOURCE)
	@echo ctx.c has been updated.

extract_sotn: $(SOTNDISK)
	$(SOTNDISK) extract iso/sotn.cue iso/
disk: build $(SOTNDISK)
	mkdir -p $(DISK_DIR)
	cp -r iso/* $(DISK_DIR)
	cp $(BUILD_DIR)/main.exe $(DISK_DIR)/SLUS_000.67
	cp $(BUILD_DIR)/DRA.BIN $(DISK_DIR)/DRA.BIN
	cp $(BUILD_DIR)/RIC.BIN $(DISK_DIR)/BIN/RIC.BIN
	cp $(BUILD_DIR)/CEN.BIN $(DISK_DIR)/ST/CEN/CEN.BIN
	cp $(BUILD_DIR)/DRE.BIN $(DISK_DIR)/ST/DRE/DRE.BIN
	cp $(BUILD_DIR)/MAD.BIN $(DISK_DIR)/ST/MAD/MAD.BIN
	cp $(BUILD_DIR)/NO3.BIN $(DISK_DIR)/ST/NO3/NO3.BIN
	cp $(BUILD_DIR)/NP3.BIN $(DISK_DIR)/ST/NP3/NP3.BIN
	cp $(BUILD_DIR)/NZ0.BIN $(DISK_DIR)/ST/NZ0/NZ0.BIN
	cp $(BUILD_DIR)/RWRP.BIN $(DISK_DIR)/ST/RWRP/RWRP.BIN
	cp $(BUILD_DIR)/SEL.BIN $(DISK_DIR)/ST/SEL/SEL.BIN
	cp $(BUILD_DIR)/ST0.BIN $(DISK_DIR)/ST/ST0/ST0.BIN
	cp $(BUILD_DIR)/WRP.BIN $(DISK_DIR)/ST/WRP/WRP.BIN
	$(SOTNDISK) make $(BUILD_DIR)/sotn.cue $(DISK_DIR) $(CONFIG_DIR)/slus00067.lba


require-tools: $(SPLAT_APP) $(ASMDIFFER_APP) $(GO)
update-dependencies: require-tools $(M2CTX_APP) $(M2C_APP)
	pip3 install -r $(TOOLS_DIR)/requirements-python.txt
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/aspatch@latest
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/gfxsotn@latest
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/sotn-disk@latest

$(SPLAT_APP):
	git submodule init $(SPLAT_DIR)
	git submodule update $(SPLAT_DIR)
	pip3 install -r $(TOOLS_DIR)/requirements-python.txt
$(ASMDIFFER_APP):
	git submodule init $(ASMDIFFER_DIR)
	git submodule update $(ASMDIFFER_DIR)
$(M2CTX_APP):
	curl -o $@ https://raw.githubusercontent.com/ethteck/m2ctx/main/m2ctx.py
$(M2C_APP):
	git submodule init $(M2C_DIR)
	git submodule update $(M2C_DIR)
	python3 -m pip install --upgrade pycparser
$(GO):
	curl -L -o go1.19.3.linux-amd64.tar.gz https://go.dev/dl/go1.19.3.linux-amd64.tar.gz
	tar -C $(TOOLS_DIR) -xzf go1.19.3.linux-amd64.tar.gz
	rm go1.19.3.linux-amd64.tar.gz
$(ASPATCH): $(GO)
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/aspatch@latest
$(SOTNDISK): $(GO)
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/sotn-disk@latest

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -Map %.map -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(ASPATCH)
	$(CPP) $(CPP_FLAGS) $< | $(CC) $(CC_FLAGS) | $(ASPATCH) | $(AS) $(AS_FLAGS) -o $@

SHELL = /bin/bash -e -o pipefail

.PHONY: all, clean, format, check, expected
.PHONY: main, dra, ric, dre, mad, no3, np3, st0, wrp, rwrp
.PHONY: %_dirs
.PHONY: extract, extract_%
.PHONY: require-tools,update-dependencies
