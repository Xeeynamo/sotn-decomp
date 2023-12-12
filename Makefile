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
PSXCC_FLAGS		:= -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff
CC_FLAGS        += -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -g
CPP_FLAGS       += -Iinclude -undef -Wall -fno-builtin
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DNO_LOGS -DHACKS -DUSE_INCLUDE_ASM
CPP_FLAGS       += -D_internal_version_$(VERSION) -DSOTN_STR
LD_FLAGS		:= -nostdlib --no-check-sections

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
MAIN_ASM_DIRS   := $(ASM_DIR)/$(MAIN) $(ASM_DIR)/$(MAIN)/psxsdk $(ASM_DIR)/$(MAIN)/psxsdk/libc $(ASM_DIR)/$(MAIN)/psxsdk/libc2 $(ASM_DIR)/$(MAIN)/psxsdk/libapi $(ASM_DIR)/$(MAIN)/psxsdk/libetc $(ASM_DIR)/$(MAIN)/psxsdk/libcard $(ASM_DIR)/$(MAIN)/psxsdk/libgpu $(ASM_DIR)/$(MAIN)/psxsdk/libgs $(ASM_DIR)/$(MAIN)/psxsdk/libgte $(ASM_DIR)/$(MAIN)/psxsdk/libcd $(ASM_DIR)/$(MAIN)/psxsdk/libsnd $(ASM_DIR)/$(MAIN)/psxsdk/libspu $(ASM_DIR)/$(MAIN)/data
MAIN_SRC_DIRS   := $(SRC_DIR)/$(MAIN) $(SRC_DIR)/$(MAIN)/psxsdk $(SRC_DIR)/$(MAIN)/psxsdk/libc $(SRC_DIR)/$(MAIN)/psxsdk/libc2 $(SRC_DIR)/$(MAIN)/psxsdk/libapi $(SRC_DIR)/$(MAIN)/psxsdk/libetc $(SRC_DIR)/$(MAIN)/psxsdk/libcard $(SRC_DIR)/$(MAIN)/psxsdk/libgpu $(SRC_DIR)/$(MAIN)/psxsdk/libgs $(SRC_DIR)/$(MAIN)/psxsdk/libgte $(SRC_DIR)/$(MAIN)/psxsdk/libcd $(SRC_DIR)/$(MAIN)/psxsdk/libsnd $(SRC_DIR)/$(MAIN)/psxsdk/libspu
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
SOTNSTR			:= $(PYTHON) $(TOOLS_DIR)/sotn-str.py process
MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py
MASPSX          := $(PYTHON) $(MASPSX_APP) --no-macro-inc --expand-div
GO              := $(HOME)/go/bin/go
GOPATH          := $(HOME)/go
SOTNDISK        := $(GOPATH)/bin/sotn-disk
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py

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

define list_shared_src_files
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/*.c))
endef

define list_shared_o_files
	$(foreach file,$(call list_shared_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

define link
	$(LD) $(LD_FLAGS) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(1).ld \
		-T $(CONFIG_DIR)/symbols.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).$(1).txt
endef

.PHONY: build

all: build check
build: build_$(VERSION)
build_us: main dra weapon ric cen dre mad no3 np3 nz0 sel st0 wrp rwrp tt_000
build_hd: dra
clean:
	git clean -fdx assets/
	git clean -fdx asm/
	git clean -fdx build/
	git clean -fdx config/
	git clean -fdx function_calls/
	git clean -fdx sotn_calltree.txt
format:
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.c")
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.h")
	clang-format -i $$(find $(INCLUDE_DIR)/ -type f -name "*.h")
	cargo run --release --manifest-path ./tools/lints/sotn-lint/Cargo.toml ./src
	black tools/*.py
	black tools/splat_ext/*.py
	black tools/split_jpt_yaml/*.py
	VERSION=us $(PYTHON) ./tools/symbols.py sort
	VERSION=hd $(PYTHON) ./tools/symbols.py sort
	./tools/symbols.py remove-orphans config/splat.us.dra.yaml
	./tools/symbols.py remove-orphans config/splat.hd.dra.yaml
	./tools/symbols.py remove-orphans config/splat.us.ric.yaml
	./tools/symbols.py remove-orphans config/splat.us.stcen.yaml
	./tools/symbols.py remove-orphans config/splat.us.stdre.yaml
	./tools/symbols.py remove-orphans config/splat.us.stno3.yaml
	./tools/symbols.py remove-orphans config/splat.us.stnp3.yaml
	./tools/symbols.py remove-orphans config/splat.us.stnz0.yaml
	./tools/symbols.py remove-orphans config/splat.us.stsel.yaml
	./tools/symbols.py remove-orphans config/splat.us.stst0.yaml
	./tools/symbols.py remove-orphans config/splat.us.stwrp.yaml
	./tools/symbols.py remove-orphans config/splat.us.strwrp.yaml
	./tools/symbols.py remove-orphans config/splat.us.tt_000.yaml
	./tools/symbols.py remove-orphans config/splat.us.stmad.yaml
patch:
	$(DIRT_PATCHER) config/dirt.$(VERSION).json
check: patch
	sha1sum --check config/check.$(VERSION).sha
expected: check
	mkdir -p expected/build
	rm -rf expected/build/$(VERSION)
	cp -r build/$(VERSION) expected/build/

main: main_dirs $(MAIN_TARGET).exe
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(MAIN_TARGET).exe: $(MAIN_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(MAIN_TARGET).elf: $(MAIN_O_FILES)
	$(LD) $(LD_FLAGS) -o $@ \
	-Map $(MAIN_TARGET).map \
	-T $(BUILD_DIR)/main.ld \
	-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(MAIN).txt

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
	printf '\x00' | dd of=$@ bs=1 seek=40959 count=1 conv=notrunc

mad_fix: stmad_dirs $$(call list_o_files,st/mad) $$(call list_o_files,st)
	$(LD) $(LD_FLAGS) -o $(BUILD_DIR)/stmad_fix.elf \
		-Map $(BUILD_DIR)/stmad_fix.map \
		-T $(BUILD_DIR)/stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt
	$(OBJCOPY) -O binary $(BUILD_DIR)/stmad_fix.elf $(BUILD_DIR)/MAD.BIN

tt_%_dirs:
	$(foreach dir,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
st%_dirs:
	$(foreach dir,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call list_o_files,servant/tt_$$*)
	$(call link,tt_$*,$@)
$(BUILD_DIR)/stmad.elf: $$(call list_o_files,st/mad) $$(call list_shared_o_files,st)
	$(LD) $(LD_FLAGS) -o $@ \
		-Map $(BUILD_DIR)/stmad.map \
		-T $(BUILD_DIR)/stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.beta.txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt
$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/$$*) $$(call list_shared_o_files,st)
	$(call link,st$*,$@)

# Weapon overlays
WEAPON0_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f0_$(num).bin $(BUILD_DIR)/weapon/w0_$(num).bin)
WEAPON1_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f1_$(num).bin $(BUILD_DIR)/weapon/w1_$(num).bin)
WEAPON_DIRS   := $(BUILD_DIR)/$(ASSETS_DIR)/weapon $(BUILD_DIR)/$(ASM_DIR)/weapon/data $(BUILD_DIR)/$(SRC_DIR)/weapon $(BUILD_DIR)/weapon
weapon: $(WEAPON_DIRS) $(BUILD_DIR)/WEAPON0.BIN
$(WEAPON_DIRS):
	@mkdir -p $@
$(BUILD_DIR)/WEAPON0.BIN: $(WEAPON0_FILES)
	cat $^ > $@
$(BUILD_DIR)/weapon/f%.bin: $(BUILD_DIR)/weapon/f%.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/weapon/w%.bin: $(BUILD_DIR)/weapon/w%.elf
	$(OBJCOPY) -O binary $< $@
	printf '\x00' | dd of=$@ bs=1 seek=12287 count=1 conv=notrunc
$(BUILD_DIR)/weapon/w0_%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/header.c.o $(BUILD_DIR)/$(ASSETS_DIR)/weapon/w_%_1.animset.o $(BUILD_DIR)/$(ASSETS_DIR)/weapon/w_%_2.animset.o $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/w0_$*.map \
		-T weapon0.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
$(BUILD_DIR)/weapon/w1_%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/header.c.o $(BUILD_DIR)/$(ASSETS_DIR)/weapon/w_%_1.animset.o $(BUILD_DIR)/$(ASSETS_DIR)/weapon/w_%_2.animset.o $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/w1_$*.map \
		-T weapon1.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o: $(SRC_DIR)/weapon/w_%.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) -lang-c -DW_$* $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_029.c.o: $(SRC_DIR)/weapon/w_029.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) -lang-c -DW_029 $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) -O1 | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/weapon/f0_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/weapon/f1_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o: $(ASSETS_DIR)/weapon/%.png
	./tools/png2bin.py $< $@
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%_1.animset.o: $(ASSETS_DIR)/weapon/%_1.animset.json
	./tools/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_1.animset.s -s g_Animset
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_1.animset.s
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%_2.animset.o: $(ASSETS_DIR)/weapon/%_2.animset.json
	./tools/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_2.animset.s -s g_Animset2
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_2.animset.s

extract: extract_$(VERSION)

include Makefile.*.mk

# Force to extract all the assembly code regardless if a function is already decompiled
force_extract:
	mv src src_tmp
	rm $(BUILD_DIR)/*.ld
	make extract -j
	rm -rf src/
	mv src_tmp src

# Rewrites symbol list from a successful build
force_symbols:
	$(PYTHON) ./tools/symbols.py map build/us/dra.map > config/symbols.us.dra.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stcen.map > config/symbols.us.stcen.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stdre.map > config/symbols.us.stdre.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stmad.map > config/symbols.us.stmad.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stno3.map > config/symbols.us.stno3.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stnp3.map > config/symbols.us.stnp3.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stnz0.map > config/symbols.us.stnz0.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stsel.map > config/symbols.us.stsel.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stst0.map > config/symbols.us.stst0.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/stwrp.map > config/symbols.us.stwrp.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/strwrp.map > config/symbols.us.strwrp.txt --no-default
	$(PYTHON) ./tools/symbols.py map build/us/tt_000.map > config/symbols.us.tt_000.txt --no-default

context:
	$(M2CTX) $(SOURCE)
	@echo ctx.c has been updated.

extract_disk: extract_disk_$(VERSION)
disk_prepare: build $(SOTNDISK)
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
disk: disk_prepare
	$(SOTNDISK) make build/sotn.$(VERSION).cue $(DISK_DIR) $(CONFIG_DIR)/disk.us.lba
disk_debug: disk_prepare
	cd tools/sotn-debugmodule && make
	cp $(BUILD_DIR)/../sotn-debugmodule.bin $(DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make build/sotn.$(VERSION).cue $(DISK_DIR) $(CONFIG_DIR)/disk.us.lba

update-dependencies: $(SPLAT_APP) $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(MASPSX_APP) $(SATURN_SPLITTER_APP) $(GO)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release
	pip3 install -r $(TOOLS_DIR)/requirements-python.txt
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/gfxsotn@latest
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/sotn-disk@latest
	git clean -fd bin/

bin/%: bin/%.tar.gz
	sha256sum --check $<.sha256
	cd bin && tar -xzf ../$<
	rm $<
	touch $@
bin/%.tar.gz: bin/%.tar.gz.sha256
	wget -O $@ https://github.com/Xeeynamo/sotn-decomp/releases/download/cc1-psx-26/$*.tar.gz
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

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

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
$(BUILD_DIR)/$(ASSETS_DIR)/%.animset.json.o: $(ASSETS_DIR)/%.animset.json
	./tools/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.json.o: $(ASSETS_DIR)/%.json
	./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
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

include tools/tools.mk

.PHONY: all, clean, format, check, build, expected
.PHONY: main, dra, ric, cen, dre, mad, no3, np3, nz0, st0, wrp, rwrp, tt_000
.PHONY: %_dirs
.PHONY: extract, extract_%
.PHONY: update-dependencies
