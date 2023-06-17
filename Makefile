.SECONDEXPANSION:
.SECONDARY:

# Binaries
VERSION         ?= us
MAIN            := main
DRA             := dra

# Compilers
CC1PSX          := ./bin/cc1-psx-26
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := $(CC1PSX)
LD              := $(CROSS)ld
CPP             := $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
CC_FLAGS        += -mcpu=3000 -quiet -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fgnu-linker -mgas -msoft-float -gcoff
CPP_FLAGS       += -Iinclude -undef -Wall -lang-c -fno-builtin
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DHACKS
CPP_FLAGS       += -D_internal_version_$(VERSION)

# Directories
ASM_DIR         := asm/$(VERSION)
SRC_DIR         := src
ASSETS_DIR      := assets
INCLUDE_DIR     := include
BUILD_DIR       := build/$(VERSION)
DISK_DIR        := $(BUILD_DIR)/${VERSION}/disk
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
M2C_ARGS        := -P 4
MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py
MASPSX          := $(PYTHON) $(MASPSX_APP) --no-macro-inc --expand-div
GO              := $(HOME)/go/bin/go
GOPATH          := $(HOME)/go
SOTNDISK        := $(GOPATH)/bin/sotn-disk
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
SATURN_SPLITTER_DIR := $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
SATURN_ADPCM_EXTRACT_APP := $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

define list_src_files
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(SRC_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**))
endef

define list_o_files
	$(foreach file,$(call list_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

define link
	$(LD) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(1).ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).$(1).txt \
		--no-check-sections \
		-nostdlib \
		-s
endef

all: build check
build: main dra ric cen dre mad no3 np3 nz0 sel st0 wrp rwrp tt_000
clean:
	git clean -fdx assets/
	git clean -fdx asm/
	git clean -fdx build/
	git clean -fdx config/
format:
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.c")
	clang-format -i $$(find $(INCLUDE_DIR)/ -type f -name "*.h")
	$(PYTHON) ./tools/symbols.py sort
check:
	sha1sum --check config/check.$(VERSION).sha
expected: check
	mkdir -p expected
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
	-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(MAIN).txt \
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

cen: stcen_dirs $(BUILD_DIR)/CEN.BIN $(BUILD_DIR)/F_CEN.BIN
$(BUILD_DIR)/CEN.BIN: $(BUILD_DIR)/stcen.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_CEN.BIN:
	$(GFXSTAGE) e assets/st/cen $@

dre: stdre_dirs $(BUILD_DIR)/DRE.BIN $(BUILD_DIR)/F_DRE.BIN
$(BUILD_DIR)/DRE.BIN: $(BUILD_DIR)/stdre.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_DRE.BIN:
	$(GFXSTAGE) e assets/st/dre $@

mad: stmad_dirs $(BUILD_DIR)/MAD.BIN $(BUILD_DIR)/F_MAD.BIN
$(BUILD_DIR)/MAD.BIN: $(BUILD_DIR)/stmad.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_MAD.BIN:
	$(GFXSTAGE) e assets/st/mad $@

no3: stno3_dirs $(BUILD_DIR)/NO3.BIN $(BUILD_DIR)/F_NO3.BIN
$(BUILD_DIR)/NO3.BIN: $(BUILD_DIR)/stno3.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NO3.BIN:
	$(GFXSTAGE) e assets/st/no3 $@

np3: stnp3_dirs $(BUILD_DIR)/NP3.BIN $(BUILD_DIR)/F_NP3.BIN
$(BUILD_DIR)/NP3.BIN: $(BUILD_DIR)/stnp3.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NP3.BIN:
	$(GFXSTAGE) e assets/st/np3 $@

nz0: stnz0_dirs $(BUILD_DIR)/NZ0.BIN $(BUILD_DIR)/F_NZ0.BIN
$(BUILD_DIR)/NZ0.BIN: $(BUILD_DIR)/stnz0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NZ0.BIN:
	$(GFXSTAGE) e assets/st/nz0 $@

sel: stsel_dirs $(BUILD_DIR)/SEL.BIN
$(BUILD_DIR)/SEL.BIN: $(BUILD_DIR)/stsel.elf
	$(OBJCOPY) -O binary $< $@

st0: stst0_dirs $(BUILD_DIR)/ST0.BIN $(BUILD_DIR)/F_ST0.BIN
$(BUILD_DIR)/ST0.BIN: $(BUILD_DIR)/stst0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_ST0.BIN:
	$(GFXSTAGE) e assets/st/st0 $@

wrp: stwrp_dirs $(BUILD_DIR)/WRP.BIN $(BUILD_DIR)/F_WRP.BIN
$(BUILD_DIR)/WRP.BIN: $(BUILD_DIR)/stwrp.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_WRP.BIN:
	$(GFXSTAGE) e assets/st/wrp $@

rwrp: strwrp_dirs $(BUILD_DIR)/RWRP.BIN $(BUILD_DIR)/F_RWRP.BIN
$(BUILD_DIR)/RWRP.BIN: $(BUILD_DIR)/strwrp.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_RWRP.BIN:
	$(GFXSTAGE) e assets/st/rwrp $@

tt_000: tt_000_dirs $(BUILD_DIR)/TT_000.BIN
$(BUILD_DIR)/TT_000.BIN: $(BUILD_DIR)/tt_000.elf
	$(OBJCOPY) -O binary $< $@

mad_fix: stmad_dirs $$(call list_o_files,st/mad)
	$(LD) -o $(BUILD_DIR)/stmad_fix.elf \
		-Map $(BUILD_DIR)/stmad_fix.map \
		-T stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt \
		--no-check-sections \
		-nostdlib \
		-s
	$(OBJCOPY) -O binary $(BUILD_DIR)/stmad_fix.elf $(BUILD_DIR)/MAD.BIN

tt_%_dirs:
	$(foreach dir,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
st%_dirs:
	$(foreach dir,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/tt_%.elf: $$(call list_o_files,servant/tt_$$*)
	$(call link,tt_$*,$@)
$(BUILD_DIR)/stmad.elf: $$(call list_o_files,st/mad)
	$(LD) -o $@ \
		-Map $(BUILD_DIR)/stmad.map \
		-T stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.beta.txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt \
		--no-check-sections \
		-nostdlib \
		-s
$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/$$*)
	$(call link,st$*,$@)

extract: extract_main extract_dra extract_ric extract_stcen extract_stdre extract_stmad extract_stno3 extract_stnp3 extract_stnz0 extract_stsel extract_stst0 extract_stwrp extract_strwrp extract_tt_000
extract_main: $(SPLAT_APP)
	$(SPLAT) $(CONFIG_DIR)/splat.$(VERSION).$(MAIN).yaml
extract_dra: $(SPLAT_APP)
	cat $(CONFIG_DIR)/symbols.$(VERSION).txt $(CONFIG_DIR)/symbols.$(VERSION).dra.txt > $(CONFIG_DIR)/generated.symbols.$(VERSION).dra.txt
	$(SPLAT) $(CONFIG_DIR)/splat.$(VERSION).$(DRA).yaml
extract_ric: $(SPLAT_APP)
	cat $(CONFIG_DIR)/symbols.$(VERSION).txt $(CONFIG_DIR)/symbols.$(VERSION).ric.txt > $(CONFIG_DIR)/generated.symbols.$(VERSION).ric.txt
	$(SPLAT) $(CONFIG_DIR)/splat.$(VERSION).ric.yaml
extract_stmad: $(SPLAT_APP)
	cat $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt > $(CONFIG_DIR)/generated.symbols.stmad.txt
	$(SPLAT) $(CONFIG_DIR)/splat.$(VERSION).stmad.yaml
	$(GFXSTAGE) d disks/$(VERSION)/ST/MAD/F_MAD.BIN $(ASSETS_DIR)/st/mad
extract_st%: $(SPLAT_APP)
	cat $(CONFIG_DIR)/symbols.$(VERSION).txt $(CONFIG_DIR)/symbols.$(VERSION).st$*.txt > $(CONFIG_DIR)/generated.symbols.$(VERSION).st$*.txt
	$(SPLAT) $(CONFIG_DIR)/splat.$(VERSION).st$*.yaml
	$(GFXSTAGE) d disks/$(VERSION)/ST/$$(echo '$*' | tr '[:lower:]' '[:upper:]')/F_$$(echo '$*' | tr '[:lower:]' '[:upper:]').BIN $(ASSETS_DIR)/st/$*
extract_tt_%: $(SPLAT_APP)
	cat $(CONFIG_DIR)/symbols.$(VERSION).txt $(CONFIG_DIR)/symbols.$(VERSION).tt_$*.txt > $(CONFIG_DIR)/generated.symbols.$(VERSION).tt_$*.txt
	$(SPLAT) $(CONFIG_DIR)/splat.$(VERSION).tt_$*.yaml
$(CONFIG_DIR)/generated.$(VERSION).symbols.%.txt:

extract_saturn: $(SATURN_SPLITTER_APP)
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/game.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/t_bat.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/zero.bin.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/stage_02.prg.yaml

extract_saturn_pcm: $(SATURN_SPLITTER_APP)
	mkdir -p build/saturn/SD
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD01.PCM build/saturn/SD/SD01.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD02.PCM build/saturn/SD/SD02.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD03.PCM build/saturn/SD/SD03.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD04.PCM build/saturn/SD/SD04.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD05.PCM build/saturn/SD/SD05.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD06.PCM build/saturn/SD/SD06.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD07.PCM build/saturn/SD/SD07.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD08.PCM build/saturn/SD/SD08.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD09.PCM build/saturn/SD/SD09.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD0A.PCM build/saturn/SD/SD0A.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD0B.PCM build/saturn/SD/SD0B.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD0C.PCM build/saturn/SD/SD0C.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD0D.PCM build/saturn/SD/SD0D.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD0E.PCM build/saturn/SD/SD0E.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD0F.PCM build/saturn/SD/SD0F.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD10.PCM build/saturn/SD/SD10.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD11.PCM build/saturn/SD/SD11.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD12.PCM build/saturn/SD/SD12.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD13.PCM build/saturn/SD/SD13.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD14.PCM build/saturn/SD/SD14.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD15.PCM build/saturn/SD/SD15.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD16.PCM build/saturn/SD/SD16.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD17.PCM build/saturn/SD/SD17.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD18.PCM build/saturn/SD/SD18.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD19.PCM build/saturn/SD/SD19.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD1A.PCM build/saturn/SD/SD1A.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD1B.PCM build/saturn/SD/SD1B.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD1C.PCM build/saturn/SD/SD1C.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD1D.PCM build/saturn/SD/SD1D.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD1E.PCM build/saturn/SD/SD1E.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD1F.PCM build/saturn/SD/SD1F.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD20.PCM build/saturn/SD/SD20.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD21.PCM build/saturn/SD/SD21.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD22.PCM build/saturn/SD/SD22.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD23.PCM build/saturn/SD/SD23.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD24.PCM build/saturn/SD/SD24.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD25.PCM build/saturn/SD/SD25.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD26.PCM build/saturn/SD/SD26.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD27.PCM build/saturn/SD/SD27.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD28.PCM build/saturn/SD/SD28.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD29.PCM build/saturn/SD/SD29.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD2A.PCM build/saturn/SD/SD2A.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD2B.PCM build/saturn/SD/SD2B.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD2C.PCM build/saturn/SD/SD2C.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD2D.PCM build/saturn/SD/SD2D.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD2E.PCM build/saturn/SD/SD2E.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD2F.PCM build/saturn/SD/SD2F.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD30.PCM build/saturn/SD/SD30.wav
	$(SATURN_ADPCM_EXTRACT_APP) disks/saturn/SD/SD31.PCM build/saturn/SD/SD31.wav

# Force to extract all the assembly code regardless if a function is already decompiled
force_extract:
	mv src src_tmp
	make extract -j
	rm -rf src/
	mv src_tmp src

context:
	$(M2CTX) $(SOURCE)
	@echo ctx.c has been updated.

extract_disk: extract_disk_$(VERSION)
extract_disk_us: extract_disk_ps1us
extract_disk_hd: extract_disk_pspeu
extract_disk_psp%:
	mkdir -p disks/psp$*
	7z x disks/sotn.psp$*.iso -odisks/psp$*/
extract_disk_ps1%: $(SOTNDISK)
	$(SOTNDISK) extract disks/sotn.$*.cue disks/$*
extract_disk_saturn:
	bchunk disks/sotn.saturn.bin disks/sotn.saturn.cue disks/sotn.saturn.iso
	7z x disks/sotn.saturn.iso01.iso -odisks/saturn/ || true
disk: build $(SOTNDISK)
	mkdir -p $(DISK_DIR)
	cp -r disks/${VERSION}/* $(DISK_DIR)
	cp $(BUILD_DIR)/main.exe $(DISK_DIR)/SLUS_000.67
	cp $(BUILD_DIR)/DRA.BIN $(DISK_DIR)/DRA.BIN
	cp $(BUILD_DIR)/RIC.BIN $(DISK_DIR)/BIN/RIC.BIN
	cp $(BUILD_DIR)/CEN.BIN $(DISK_DIR)/ST/CEN/CEN.BIN
	cp $(BUILD_DIR)/F_CEN.BIN $(DISK_DIR)/ST/CEN/F_CEN.BIN
	cp $(BUILD_DIR)/DRE.BIN $(DISK_DIR)/ST/DRE/DRE.BIN
	cp $(BUILD_DIR)/F_DRE.BIN $(DISK_DIR)/ST/DRE/F_DRE.BIN
	cp $(BUILD_DIR)/MAD.BIN $(DISK_DIR)/ST/MAD/MAD.BIN
	cp $(BUILD_DIR)/F_MAD.BIN $(DISK_DIR)/ST/MAD/F_MAD.BIN
	cp $(BUILD_DIR)/NO3.BIN $(DISK_DIR)/ST/NO3/NO3.BIN
	cp $(BUILD_DIR)/F_NO3.BIN $(DISK_DIR)/ST/NO3/F_NO3.BIN
	cp $(BUILD_DIR)/NP3.BIN $(DISK_DIR)/ST/NP3/NP3.BIN
	cp $(BUILD_DIR)/F_NP3.BIN $(DISK_DIR)/ST/NP3/F_NP3.BIN
	cp $(BUILD_DIR)/NZ0.BIN $(DISK_DIR)/ST/NZ0/NZ0.BIN
	cp $(BUILD_DIR)/F_NZ0.BIN $(DISK_DIR)/ST/NZ0/F_NZ0.BIN
	cp $(BUILD_DIR)/RWRP.BIN $(DISK_DIR)/ST/RWRP/RWRP.BIN
	cp $(BUILD_DIR)/F_RWRP.BIN $(DISK_DIR)/ST/RWRP/F_RWRP.BIN
	cp $(BUILD_DIR)/SEL.BIN $(DISK_DIR)/ST/SEL/SEL.BIN
	cp $(BUILD_DIR)/ST0.BIN $(DISK_DIR)/ST/ST0/ST0.BIN
	cp $(BUILD_DIR)/F_ST0.BIN $(DISK_DIR)/ST/ST0/F_ST0.BIN
	cp $(BUILD_DIR)/WRP.BIN $(DISK_DIR)/ST/WRP/WRP.BIN
	cp $(BUILD_DIR)/F_WRP.BIN $(DISK_DIR)/ST/WRP/F_WRP.BIN
	cp $(BUILD_DIR)/TT_000.BIN $(DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make build/sotn.$(VERSION).cue $(DISK_DIR) $(CONFIG_DIR)/disk.us.lba

update-dependencies: $(SPLAT_APP) $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(MASPSX_APP) $(SATURN_SPLITTER_APP) $(GO)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release
	pip3 install -r $(TOOLS_DIR)/requirements-python.txt
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/gfxsotn@latest
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/sotn-disk@latest
	git clean -fd bin/

bin/%:
	cd ./bin && wget https://github.com/Xeeynamo/sotn-decomp/releases/download/$*/$*.tar.gz
	rm -f $*.tar.gz*
	cd ./bin && sha256sum --check $*.tar.gz.sha256 && tar -xzf $*.tar.gz
	rm -f $*.tar.gz*
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
$(MASPSX_APP):
	git submodule init $(MASPSX_DIR)
	git submodule update $(MASPSX_DIR)
$(GO):
	curl -L -o go1.19.7.linux-amd64.tar.gz https://go.dev/dl/go1.19.7.linux-amd64.tar.gz
	tar -C $(HOME) -xzf go1.19.7.linux-amd64.tar.gz
	rm go1.19.7.linux-amd64.tar.gz
$(SOTNDISK): $(GO)
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/sotn-disk@latest

$(SATURN_SPLITTER_APP):
	git submodule init $(SATURN_SPLITTER_DIR)
	git submodule update $(SATURN_SPLITTER_DIR)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) $< | $(CC) $(CC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

build_saturn_dosemu_docker_container:
	docker build -t dosemu:latest -f tools/saturn_toolchain/dosemu_dockerfile .

build_saturn_binutils_docker_container:
	docker build -t binutils-sh-elf:latest -f tools/saturn_toolchain/binutils_dockerfile .

build_saturn_toolchain_gccsh:
	# get GCCSH
	wget -nc https://github.com/sozud/saturn-compilers/archive/refs/heads/main.zip
	unzip -n main.zip
	rm -rf ./tools/saturn_toolchain/GCCSH
	mv saturn-compilers-main/cygnus-2.7-96Q3-bin ./tools/saturn_toolchain/GCCSH
	rm -rf main.zip
	rm -rf saturn-compilers-main

# parallel OK
build_saturn_toolchain: build_saturn_dosemu_docker_container build_saturn_binutils_docker_container build_saturn_toolchain_gccsh $(SATURN_SPLITTER_APP)

# CI prep, don't build dosemu container (parallel OK)
saturn_ci_tasks: extract_disk_saturn build_saturn_binutils_docker_container build_saturn_toolchain_gccsh $(SATURN_SPLITTER_APP)

SATURN_BUILD_DIR := build/saturn
# absolute path for docker mounts
SATURN_BUILD_ABS := $(shell pwd)/$(SATURN_BUILD_DIR)
SATURN_DISK_DIR := disks/saturn
# absolute path for docker mounts
SATURN_DISK_ABS := $(shell pwd)/$(SATURN_DISK_DIR)

build_saturn_copy_files:
	# copy everything into same directory since dosemu is hard to use otherwise
	rm -rf $(SATURN_BUILD_DIR)
	mkdir -p $(SATURN_BUILD_DIR)
	cp -r ./tools/saturn_toolchain/GCCSH/* $(SATURN_BUILD_DIR)
	cp  ./src/saturn/inc_asm.h $(SATURN_BUILD_DIR)
	cp  ./src/saturn/macro.inc $(SATURN_BUILD_DIR)
	cp  ./src/saturn/game.c $(SATURN_BUILD_DIR)
	cp  ./src/saturn/t_bat.c $(SATURN_BUILD_DIR)
	cp  ./src/saturn/zero.c $(SATURN_BUILD_DIR)
	cp  ./src/saturn/stage_02.c $(SATURN_BUILD_DIR)
	cp  ./src/saturn/sattypes.h $(SATURN_BUILD_DIR)
	mkdir -p $(SATURN_BUILD_DIR)/asm/saturn/
	mkdir -p $(SATURN_BUILD_DIR)/asm/saturn/
	cp -r ./asm/saturn/game $(SATURN_BUILD_DIR)/asm/saturn/game
	cp -r ./asm/saturn/t_bat $(SATURN_BUILD_DIR)/asm/saturn/t_bat
	cp -r ./asm/saturn/zero $(SATURN_BUILD_DIR)/asm/saturn/zero
	cp -r ./asm/saturn/stage_02 $(SATURN_BUILD_DIR)/asm/saturn/stage_02
	cp  ./tools/saturn_toolchain/compile_dosemu.sh $(SATURN_BUILD_DIR)
	chmod +x $(SATURN_BUILD_DIR)/compile_dosemu.sh

build_saturn_dosemu_native:
	cd build/saturn && FILENAME=game sh ./compile_dosemu.sh
	cd build/saturn && FILENAME=t_bat sh ./compile_dosemu.sh
	cd build/saturn && FILENAME=zero sh ./compile_dosemu.sh
	cd build/saturn && FILENAME=stage_02 sh ./compile_dosemu.sh

build_saturn_dosemu_docker:
	docker run --rm -e FILENAME=game -v $(SATURN_BUILD_ABS):/build -w /build dosemu:latest /bin/bash -c "./compile_dosemu.sh"
	docker run --rm -e FILENAME=t_bat -v $(SATURN_BUILD_ABS):/build -w /build dosemu:latest /bin/bash -c "./compile_dosemu.sh"
	docker run --rm -e FILENAME=zero -v $(SATURN_BUILD_ABS):/build -w /build dosemu:latest /bin/bash -c "./compile_dosemu.sh"
	docker run --rm -e FILENAME=stage_02 -v $(SATURN_BUILD_ABS):/build -w /build dosemu:latest /bin/bash -c "./compile_dosemu.sh"

build_saturn_link:
	# link
	cat ./config/saturn/game_syms.txt > ./build/saturn/all_syms.txt
	cat ./config/saturn/t_bat_syms.txt >> ./build/saturn/all_syms.txt
	cat ./config/saturn/zero_syms.txt >> ./build/saturn/all_syms.txt
	cp ./config/saturn/t_bat_user_syms.txt ./build/saturn/
	cp ./config/saturn/game_user_syms.txt ./build/saturn/
	cp ./config/saturn/stage_02_user_syms.txt ./build/saturn/

	cp ./config/saturn/*.ld ./build/saturn
	docker run --rm -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c "sh-elf-ld -o zero_li.o -Map zero.map -T zero.ld -T all_syms.txt -verbose zero.o --no-check-sections -nostdlib -s"
	docker run --rm -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c "sh-elf-ld -o t_bat_li.o -Map t_bat.map -T t_bat.ld -T all_syms.txt -T t_bat_user_syms.txt -verbose t_bat.o --no-check-sections -nostdlib -s"
	docker run --rm -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c "sh-elf-ld -o game_li.o -Map game.map -T game.ld -T all_syms.txt -T game_user_syms.txt -verbose game.o --no-check-sections -nostdlib -s"
	docker run --rm -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c "sh-elf-ld -o stage_02_li.o -Map stage_02.map -T stage_02.ld -T all_syms.txt -T stage_02_user_syms.txt -verbose stage_02.o --no-check-sections -nostdlib -s"

# do not run in parallel
build_saturn: build_saturn_copy_files build_saturn_dosemu_docker build_saturn_link

# do not run in parallel
build_saturn_ci: build_saturn_copy_files build_saturn_dosemu_native build_saturn_link

check_saturn:
	# dump binaries using sh binutils container
	chmod +x tools/saturn_toolchain/strip.sh
	cp tools/saturn_toolchain/strip.sh $(SATURN_BUILD_DIR)
	docker run --rm -e INPUT_FILENAME=game_li.o -e OUTPUT_FILENAME=GAME.PRG -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c ./strip.sh
	docker run --rm -e INPUT_FILENAME=t_bat_li.o -e OUTPUT_FILENAME=T_BAT.PRG -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c ./strip.sh
	docker run --rm -e INPUT_FILENAME=zero_li.o -e OUTPUT_FILENAME=0.BIN -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c ./strip.sh
	docker run --rm -e INPUT_FILENAME=stage_02_li.o -e OUTPUT_FILENAME=STAGE_02.PRG -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c ./strip.sh
	# check hashes
	sha1sum --check config/saturn/check.saturn.sha

diff_saturn:
	chmod +x tools/saturn_toolchain/diff.sh
	cp tools/saturn_toolchain/diff.sh $(SATURN_BUILD_DIR)
	docker run --rm -e FILENAME=$(FILENAME) -v $(SATURN_DISK_ABS):/theirs -v $(SATURN_BUILD_ABS):/build -w /build binutils-sh-elf:latest /bin/bash -c ./diff.sh

# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.layoutobj.json.o: $(ASSETS_DIR)/%.layoutobj.json
	./tools/splat_ext/layoutobj.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
$(BUILD_DIR)/$(ASSETS_DIR)/%.roomdef.json.o: $(ASSETS_DIR)/%.roomdef.json
	./tools/splat_ext/roomdef.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
$(BUILD_DIR)/$(ASSETS_DIR)/%.layers.json.o: $(ASSETS_DIR)/%.layers.json
	./tools/splat_ext/layers.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.tiledef.json.o: $(ASSETS_DIR)/%.tiledef.json
	./tools/splat_ext/tiledef.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	./tools/splat_ext/spritesheet.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.spriteparts.json.o: $(ASSETS_DIR)/%.spriteparts.json
	./tools/splat_ext/spriteparts.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
$(BUILD_DIR)/$(ASSETS_DIR)/%.equipment.json.o: $(ASSETS_DIR)/%.equipment.json
	./tools/splat_ext/equipment.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.bin
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritepartslist.json.o: $(ASSETS_DIR)/%.spritepartslist.json
	./tools/splat_ext/spritepartslist.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.tilelayout.bin.o: $(ASSETS_DIR)/%.tilelayout.bin
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(ASSETS_DIR)/$*.tilelayout.bin
$(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.dec.o: $(ASSETS_DIR)/%.dec
# for now '.dec' files are ignored
	touch $@
$(BUILD_DIR)/$(ASSETS_DIR)/%.png.o: $(ASSETS_DIR)/%.png
	touch $@

SHELL = /bin/bash -e -o pipefail

.PHONY: all, clean, format, check, expected
.PHONY: main, dra, ric, cen, dre, mad, no3, np3, nz0, st0, wrp, rwrp, tt_000
.PHONY: %_dirs
.PHONY: extract, extract_%
.PHONY: require-tools,update-dependencies
