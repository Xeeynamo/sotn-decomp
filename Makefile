.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all

# Variables
# User environment
VERSION         ?= us

# VERSION=us
# main dra ric weapon
PSX_US_GAME		:= main dra ric weapon
# are cat cen chi dai dre lib mad no0 no1 no2 no3 no4 np3 nz0 nz1 sel st0 top wrp
PSX_US_STAGE	:= cen chi dre lib no0 no1 no3 np3 nz0 st0 wrp mad sel no4
# rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp
PSX_US_REV_STAGE:= rwrp
# bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8
PSX_US_ALL_BOSS	:= bo4 mar rbo3
# tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006
PSX_US_SERVANT	:= tt_000 tt_001 tt_002 tt_003 tt_004

# VERSION=hd
PSX_HD_GAME		:= dra ric
PSX_HD_STAGE	:= cen wrp
PSX_HD_REV_STAGE:= 
PSX_HD_ALL_BOSS	:= 
PSX_HD_SERVANTS	:= tt_000

# VERSION=pspeu
PSP_EU_GAME		:= dra
PSP_EU_STAGE	:= lib no4 st0 wrp
PSP_EU_REV_STAGE:= 
PSP_EU_ALL_BOSS	:= 
PSP_EU_SERVANTS	:= tt_000

# VERSION=saturn
SATURN_GAME		:= GAME ALUCARD
SATURN_STAGE	:= STAGE_02 WARP
SATURN_REV_STAGE:= 
SATURN_ALL_BOSS := 
SATURN_SERVANTS	:= T_BAT

ifeq ($(VERSION),us)
VERSION_PREFIX := PSX_US
else ifeq ($(VERSION),hd)
VERSION_PREFIX := PSX_HD
else ifeq ($(VERSION),pspeu)
VERSION_PREFIX := PSP_EU
else ifeq ($(VERSION),saturn)
VERSION_PREFIX := SATURN
endif

$(VERSION_PREFIX)_ALLSTAGES	:= $($(VERSION_PREFIX)_STAGE) $($(VERSION_PREFIX)_REV_STAGE)
$(VERSION_PREFIX)_EXTRACT_TARGETS	:= $($(VERSION_PREFIX)_GAME) $(addprefix st,$($(VERSION_PREFIX)_ALLSTAGES)) $(addprefix bo,$($(VERSION_PREFIX)_ALL_BOSS)) $($(VERSION_PREFIX)_SERVANTS)
$(VERSION_PREFIX)_BUILD_TARGETS	:= $($(VERSION_PREFIX)_GAME) $($(VERSION_PREFIX)_ALLSTAGES) $($(VERSION_PREFIX)_ALL_BOSS) $($(VERSION_PREFIX)_SERVANTS)

# Compilers
CC1PSX          := ./bin/cc1-psx-26
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := $(CC1PSX)
LD              := $(CROSS)ld
CPP             := $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy

CC_FLAGS        += -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -g
CPP_FLAGS       += -Iinclude -Iinclude/psxsdk -undef -Wall -fno-builtin
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DNO_LOGS -DHACKS -DUSE_INCLUDE_ASM
CPP_FLAGS       += -D_internal_version_$(VERSION) -DSOTN_STR
LD_FLAGS        := -nostdlib --no-check-sections

# Directories
ASM_DIR         := asm/$(VERSION)
BIN_DIR         := bin
SRC_DIR         := src
ASSETS_DIR      := assets
INCLUDE_DIR     := include
BUILD_DIR       := build/$(VERSION)
DISK_DIR        := $(BUILD_DIR)/${VERSION}/disk
CONFIG_DIR      := config
TOOLS_DIR       := tools

# Symbols
MAIN_TARGET     := $(BUILD_DIR)/main
BASE_SYMBOLS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

# Tooling
PYTHON          := python3
SPLAT           := splat split
ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
ASMDIFFER_APP   := $(ASMDIFFER_DIR)/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2CTX           := $(PYTHON) $(M2CTX_APP)
M2C_DIR         := $(TOOLS_DIR)/m2c
M2C_APP         := $(M2C_DIR)/m2c.py
M2C             := $(PYTHON) $(M2C_APP)
M2C_ARGS        := -P 4
SOTNSTR         := $(PYTHON) $(TOOLS_DIR)/sotn_str/sotn_str.py process
MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py
MASPSX          := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.34
MASPSX_21       := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.21
GO              := $(HOME)/go/bin/go
GOPATH          := $(HOME)/go
SOTNDISK        := $(GOPATH)/bin/sotn-disk
SOTNASSETS      := $(GOPATH)/bin/sotn-assets
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py
SHASUM          := shasum
SATURN_SPLITTER_DIR			:= $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP 		:= $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
VENV_PATH       ?= .venv
export PATH     := $(VENV_PATH)/bin:$(PATH)

SOTNDISK_SOURCES   := $(shell find tools/sotn-disk -name '*.go')
SOTNASSETS_SOURCES := $(shell find tools/sotn-assets -name '*.go')

CHECK_FILES := $(shell cut -d' ' -f3 config/check.$(VERSION).sha)

# Platform specific variables
ifneq (,$(filter $(VERSION),us hd)) # Both us and hd versions use the PSX platform
# flags
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
PSXCC_FLAGS     := -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff

# libs
PSXLIBS         := $(addprefix lib, c c2 api etc card gpu gs gte cd snd spu)

# Files
PSXLIB_DIRS     := $(addprefix psxsdk/, . $(PSXLIBS))
PSXLIB_DATA_DIRS := $(addprefix data/, . $(PSXLIB_DIRS))
MAIN_ASM_DIRS   := $(addprefix $(ASM_DIR)/main/,. $(PSXLIB_DIRS) data $(PSXLIB_DATA_DIRS))
MAIN_SRC_DIRS   := $(addprefix $(SRC_DIR)/main/,. $(PSXLIB_DIRS))

MAIN_S_FILES    := $(wildcard $(addsuffix /*.s, $(MAIN_ASM_DIRS)))
MAIN_C_FILES    := $(wildcard $(addsuffix /*.c, $(MAIN_SRC_DIRS)))
MAIN_O_FILES    := $(patsubst %.s,%.s.o,$(MAIN_S_FILES))
MAIN_O_FILES    += $(patsubst %.c,%.c.o,$(MAIN_C_FILES))
MAIN_O_FILES    := $(addprefix $(BUILD_DIR)/,$(MAIN_O_FILES))
else ifeq ($(VERSION),pspeu)
# Flags
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
MWLDPSP_FLAGS   := -partial -nostdlib -msgstyle gcc -sym full,elf -g

# Tools
ALLEGREX_AS     := $(BIN_DIR)/allegrex-as
AS              := $(ALLEGREX_AS)
WIBO            := $(BIN_DIR)/wibo
MWCCPSP         := $(BIN_DIR)/mwccpsp.exe
CCPSP           := MWCIncludes=$(BIN_DIR) $(WIBO) $(MWCCPSP)

MWASPSP         := $(WIBO) $(BIN_DIR)/asm_psp_elf.exe -gnu
MWLDPSP         := $(WIBO) $(BIN_DIR)/mwldpsp.exe

MWCCGAP_DIR     := $(TOOLS_DIR)/mwccgap
MWCCGAP_APP     := $(MWCCGAP_DIR)/mwccgap.py
MWCCGAP         := $(PYTHON) $(MWCCGAP_APP)
else ifeq ($(VERSION),saturn)
SATURN_ASSETS_DIR := $(ASSETS_DIR)/saturn
SATURN_LIB_TARGETS	:= lib/gfs lib/spr lib/dma lib/scl lib/csh lib/per lib/cdc lib/mth lib/bup lib/sys

DOSEMU						:= dosemu
DOSEMU_FLAGS				:= -quiet -dumb -f ./dosemurc -K . -E
DOSEMU_APP					:= $(DOSEMU) $(DOSEMU_FLAGS)
SATURN_TOOLCHAIN			:= bin/cygnus-2.7-96Q3-bin
CC1_SATURN					:= $(BUILD_DIR)/CC1.EXE
SATURN_ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

SATURN_BUILD_PRGS		:= $(addprefix $(BUILD_DIR)/,$(addsuffix .PRG,$(SATURN_BUILD_TARGETS)))
SATURN_LIB_OBJECTS		:= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SATURN_LIB_TARGETS)))
SATURN_PCM_FILES 		:= $(wildcard disks/saturn/SD/*.PCM)
SATURN_WAV_FILES 		:= $(patsubst disks/saturn/SD/%.PCM,$(SATURN_ASSETS_DIR)/SD/%.wav,$(SATURN_PCM_FILES))
endif

# Functions
define list_src_files
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/handwritten,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(SRC_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**))
endef
define list_st_src_files
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/D_801*.bin))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/*.gfxbin))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/*.palbin))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/cutscene_*.bin))
endef

define list_o_files
	$(foreach file,$(call list_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

define list_st_o_files
	$(foreach file,$(call list_st_src_files,$(1)),$(BUILD_DIR)/$(file).o)
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
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).$(1).txt
endef

# Helper Functions
define list_src_files_psp
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**))
endef

define list_o_files_psp
	$(foreach file,$(call list_src_files_psp,$(1)),$(BUILD_DIR)/$(file).o)
endef

# leverages MWCC ability to compile data and text as separate sections to allow
# LD using --gc-sections and remove all the symbols that are unreferenced.
# symexport.*.txt is used to enforce a specific symbol and all its dependencies
# to be used. Refer to *.map to know which sections are being discarded by LD.
# Use nm to retrieve the symbol name out of a object file such as the mwo_header.
define link_with_deadstrip
	$(LD) $(LD_FLAGS) -o $(2) \
		--gc-sections \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(1).ld \
		-T $(CONFIG_DIR)/symexport.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).$(1).txt
endef

.PHONY: build

##@ Variables
##@
##@     VERSION              the game version to build (us, hd, pspeu, saturn, pc) (Default: us)
##@
##@ Primary Targets
##@

all: ##@ (Default) build and check
all: build check

extract: ##@ split game files into assets and assembly
extract: extract_$(VERSION)

build: ##@ build game files
build: build_$(VERSION)

clean: ##@ clean extracted files, assets, and build artifacts
	git clean -fdx assets/
	git clean -fdx asm/$(VERSION)/
	git clean -fdx build/$(VERSION)/
	git clean -fdx $(SRC_DIR)/weapon
	git clean -fdx config/*$(VERSION)*
	git clean -fdx function_calls/
	git clean -fdx sotn_calltree.txt

##@
##@ Misc Targets
##@

# this help target will find targets which are followed by a comment beging with '#' '#' '@' and
# print them in a summary form. Any comments on a line by themselves with start with `#' '#' '@'
# will act as section dividers.
.PHONY: help
help: ##@ Print listing of key targets with their descriptions
	@printf "\nUsage: make [VERSION=version] <target> …\n"
	@grep -F -h "##@" $(MAKEFILE_LIST) | grep -F -v grep -F | sed -e 's/\\$$//' | awk 'BEGIN {FS = ":*[[:space:]]*##@[[:space:]]?"}; \
	{ \
		if($$2 == "") \
			printf ""; \
		else if($$0 ~ /^#/) \
			printf "\n%s\n", $$2; \
		else if($$1 == "") \
			printf "     %-20s%s\n", "", $$2; \
		else { \
            system("tput setaf 4; printf \"\n    %-20s \" " $$1 "; tput sgr0"); \
            printf "%s\n", $$2; \
        }; \
	}'

format: ##@ Format source code, clean symbols, other linting
format: format-src format-tools format-symbols format-license

format-src: bin/clang-format
	cargo run --release --manifest-path ./tools/lints/sotn-lint/Cargo.toml ./src
	@# find explainer:
	@#    find $(SRC_DIR) $(INCLUDE_DIR)                      : look in src and include
	@#    -type d \( -name 3rd -o -name CMakeFiles \) -prune  : if an entry is both a directory and 3rd or CMakeFiles
	@#                                                          ignore it and don't traverse it
	@#    -o \( -type f \( -name '*.h' -o -name '*.c' \) \)   : or if an entry is a file and named *.h or *.c, include it
	@#    -print0                                             : print only the matching entries, delimit by NULL to
	@#                                                          ensure files with characters xargs uses as delimiters are
	@#                                                          properly handled
	find $(SRC_DIR) $(INCLUDE_DIR) \
        -type d \( -name 3rd -o -name CMakeFiles \) -prune \
        -o \( -type f \( -name '*.c' -o -name '*.h' \) \) \
        -print0 \
        | xargs -0 -n10 -P$$(nproc) bin/clang-format -i
format-tools:
	black tools/*.py
	black tools/splat_ext/*.py
	black tools/split_jpt_yaml/*.py
format-symbols:
	VERSION=us $(PYTHON) ./tools/symbols.py sort
	VERSION=hd $(PYTHON) ./tools/symbols.py sort
	VERSION=pspeu $(PYTHON) ./tools/symbols.py sort
	./tools/symbols.py remove-orphans config/splat.us.dra.yaml
	./tools/symbols.py remove-orphans config/splat.hd.dra.yaml
	./tools/symbols.py remove-orphans config/splat.us.ric.yaml
	./tools/symbols.py remove-orphans config/splat.hd.ric.yaml
	./tools/symbols.py remove-orphans config/splat.us.stcen.yaml
	./tools/symbols.py remove-orphans config/splat.hd.stcen.yaml
	./tools/symbols.py remove-orphans config/splat.us.stchi.yaml
	./tools/symbols.py remove-orphans config/splat.us.stdre.yaml
	./tools/symbols.py remove-orphans config/splat.us.stlib.yaml
	./tools/symbols.py remove-orphans config/splat.us.stno0.yaml
	./tools/symbols.py remove-orphans config/splat.us.stno1.yaml
	./tools/symbols.py remove-orphans config/splat.us.stno3.yaml
	./tools/symbols.py remove-orphans config/splat.us.stno4.yaml
	./tools/symbols.py remove-orphans config/splat.us.stnp3.yaml
	./tools/symbols.py remove-orphans config/splat.us.stnz0.yaml
	./tools/symbols.py remove-orphans config/splat.us.stsel.yaml
	./tools/symbols.py remove-orphans config/splat.us.stst0.yaml
	./tools/symbols.py remove-orphans config/splat.us.stwrp.yaml
	./tools/symbols.py remove-orphans config/splat.hd.stwrp.yaml
	./tools/symbols.py remove-orphans config/splat.us.strwrp.yaml
	./tools/symbols.py remove-orphans config/splat.us.bomar.yaml
	./tools/symbols.py remove-orphans config/splat.us.bobo4.yaml
	./tools/symbols.py remove-orphans config/splat.us.borbo3.yaml
	./tools/symbols.py remove-orphans config/splat.us.tt_000.yaml
	./tools/symbols.py remove-orphans config/splat.hd.tt_000.yaml
	./tools/symbols.py remove-orphans config/splat.us.tt_001.yaml
	./tools/symbols.py remove-orphans config/splat.us.tt_002.yaml
	./tools/symbols.py remove-orphans config/splat.us.tt_003.yaml
	./tools/symbols.py remove-orphans config/splat.us.tt_004.yaml
	./tools/symbols.py remove-orphans config/splat.us.stmad.yaml
format-license:
	find src/ | grep -E '\.c$$|\.h$$' | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | python3 ./tools/lint-license.py - AGPL-3.0-or-later
	python3 ./tools/lint-license.py include/game.h AGPL-3.0-or-later
	python3 ./tools/lint-license.py include/entity.h AGPL-3.0-or-later
	python3 ./tools/lint-license.py include/items.h AGPL-3.0-or-later
	python3 ./tools/lint-license.py include/lba.h AGPL-3.0-or-later
	python3 ./tools/lint-license.py include/memcard.h AGPL-3.0-or-later

# fast-format
ff: MAKEFLAGS += --jobs
ff:
	$(MAKE) format

patch:
	$(DIRT_PATCHER) config/dirt.$(VERSION).json
check: ##@ compare built files to original game files
check: config/check.$(VERSION).sha patch $(CHECK_FILES)
	@$(SHASUM) --check $< | awk 'BEGIN{ FS=": " }; { \
        printf "%s\t[ ", $$1; \
        if ($$2 == "OK") \
            color = 28;   \
        else \
            color = 196;   \
        system("tput setaf " color "; printf " $$2 "; tput sgr0"); \
        printf " ]\n"; \
    }' | column --separator $$'\t' --table
expected: check
	mkdir -p expected/build
	rm -rf expected/build/$(VERSION)
	cp -r build/$(VERSION) expected/build/

main: $(MAIN_TARGET).exe
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(MAIN_TARGET).exe: $(MAIN_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(MAIN_TARGET).elf: $(MAIN_O_FILES) $(BUILD_DIR)/main.ld $(CONFIG_DIR)/undefined_syms.$(VERSION).txt $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).main.txt
	$(LD) $(LD_FLAGS) -o $@ \
	-Map $(MAIN_TARGET).map \
	-T $(BUILD_DIR)/main.ld \
	-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).main.txt

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
	dd status=none if=/dev/zero of=$@ bs=1 seek=12287 count=1 conv=notrunc
$(ASM_DIR)/weapon/data/w_%.data.s: # create a fake empty file if all the data has been imported
	touch $@
$(ASM_DIR)/weapon/data/w_%.sbss.s: # create a fake empty file if all the bss section has been imported
	touch $@
$(BUILD_DIR)/weapon/w0_%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/w0_$*.map \
		-T weapon0.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
$(BUILD_DIR)/weapon/w1_%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/w1_$*.map \
		-T weapon1.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o: $(SRC_DIR)/weapon/w_%.c $(MASPSX_APP) $(CC1PSX) | weapon_dirs
	$(CPP) $(CPP_FLAGS) -lang-c -DW_$* $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_029.c.o: $(SRC_DIR)/weapon/w_029.c $(MASPSX_APP) $(CC1PSX) | weapon_dirs
	$(CPP) $(CPP_FLAGS) -lang-c -DW_029 $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) -O1 | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/weapon/f0_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o | weapon_dirs
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/weapon/f1_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o: $(ASSETS_DIR)/weapon/%.png
	./tools/png2bin.py $< $@

ifneq (,$(filter $(VERSION),us hd)) # Both us and hd versions use the PSX platform
include Makefile.psx.mk
else ifeq ($(VERSION),pspeu)
include Makefile.psp.mk
else ifeq ($(VERSION),saturn)
include Makefile.saturn.mk
endif

# Force to extract all the assembly code regardless if a function is already decompiled
force_extract:
	mv src src_tmp
	rm $(BUILD_DIR)/*.ld
	make extract -j
	rm -rf src/
	mv src_tmp src

force_symbols: ##@ Extract a full list of symbols from a successful build
	$(PYTHON) ./tools/symbols.py elf build/us/dra.elf > config/symbols.us.dra.txt
	$(PYTHON) ./tools/symbols.py elf build/us/ric.elf > config/symbols.us.ric.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stcen.elf > config/symbols.us.stcen.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stchi.elf > config/symbols.us.stchi.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stdre.elf > config/symbols.us.stdre.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stlib.elf > config/symbols.us.stlib.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stno0.elf > config/symbols.us.stno0.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stno1.elf > config/symbols.us.stno1.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stno3.elf > config/symbols.us.stno3.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stno4.elf > config/symbols.us.stno4.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stnp3.elf > config/symbols.us.stnp3.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stnz0.elf > config/symbols.us.stnz0.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stsel.elf > config/symbols.us.stsel.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stst0.elf > config/symbols.us.stst0.txt
	$(PYTHON) ./tools/symbols.py elf build/us/stwrp.elf > config/symbols.us.stwrp.txt
	$(PYTHON) ./tools/symbols.py elf build/us/strwrp.elf > config/symbols.us.strwrp.txt
	$(PYTHON) ./tools/symbols.py elf build/us/bomar.elf > config/symbols.us.bomar.txt
	$(PYTHON) ./tools/symbols.py elf build/us/bobo4.elf > config/symbols.us.bobo4.txt
	$(PYTHON) ./tools/symbols.py elf build/us/borbo3.elf > config/symbols.us.borbo3.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_000.elf > config/symbols.us.tt_000.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_001.elf > config/symbols.us.tt_001.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_002.elf > config/symbols.us.tt_002.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_003.elf > config/symbols.us.tt_003.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_004.elf > config/symbols.us.tt_004.txt

context: ##@ create a context for decomp.me. Set the SOURCE variable prior to calling this target
	VERSION=$(VERSION) $(M2CTX) $(SOURCE)
	@echo ctx.c has been updated.

extract_disk: ##@ Extract game files from a disc image.
extract_disk: extract_disk_$(VERSION)
disk_prepare: build $(SOTNDISK)
	mkdir -p $(DISK_DIR)
	cp -r disks/${VERSION}/* $(DISK_DIR)
	cp $(BUILD_DIR)/main.exe $(DISK_DIR)/SLUS_000.67
	cp $(BUILD_DIR)/DRA.BIN $(DISK_DIR)/DRA.BIN
	cp $(BUILD_DIR)/RIC.BIN $(DISK_DIR)/BIN/RIC.BIN
	cp $(BUILD_DIR)/CEN.BIN $(DISK_DIR)/ST/CEN/CEN.BIN
	cp $(BUILD_DIR)/F_CEN.BIN $(DISK_DIR)/ST/CEN/F_CEN.BIN
	cp $(BUILD_DIR)/CHI.BIN $(DISK_DIR)/ST/CHI/CHI.BIN
	cp $(BUILD_DIR)/F_CHI.BIN $(DISK_DIR)/ST/CHI/F_CHI.BIN
	cp $(BUILD_DIR)/DRE.BIN $(DISK_DIR)/ST/DRE/DRE.BIN
	cp $(BUILD_DIR)/F_DRE.BIN $(DISK_DIR)/ST/DRE/F_DRE.BIN
	cp $(BUILD_DIR)/LIB.BIN $(DISK_DIR)/ST/LIB/LIB.BIN
	cp $(BUILD_DIR)/F_LIB.BIN $(DISK_DIR)/ST/LIB/F_LIB.BIN
	cp $(BUILD_DIR)/MAD.BIN $(DISK_DIR)/ST/MAD/MAD.BIN
	cp $(BUILD_DIR)/F_MAD.BIN $(DISK_DIR)/ST/MAD/F_MAD.BIN
	cp $(BUILD_DIR)/NO0.BIN $(DISK_DIR)/ST/NO0/NO0.BIN
	cp $(BUILD_DIR)/F_NO0.BIN $(DISK_DIR)/ST/NO0/F_NO0.BIN
	cp $(BUILD_DIR)/NO1.BIN $(DISK_DIR)/ST/NO1/NO1.BIN
	cp $(BUILD_DIR)/F_NO1.BIN $(DISK_DIR)/ST/NO1/F_NO1.BIN
	cp $(BUILD_DIR)/NO3.BIN $(DISK_DIR)/ST/NO3/NO3.BIN
	cp $(BUILD_DIR)/F_NO3.BIN $(DISK_DIR)/ST/NO3/F_NO3.BIN
	cp $(BUILD_DIR)/NO4.BIN $(DISK_DIR)/ST/NO4/NO4.BIN
	cp $(BUILD_DIR)/F_NO4.BIN $(DISK_DIR)/ST/NO4/F_NO4.BIN
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
	cp $(BUILD_DIR)/MAR.BIN $(DISK_DIR)/BOSS/MAR/MAR.BIN
	cp $(BUILD_DIR)/F_MAR.BIN $(DISK_DIR)/BOSS/MAR/F_MAR.BIN
	cp $(BUILD_DIR)/BO4.BIN $(DISK_DIR)/BOSS/BO4/BO4.BIN
	cp $(BUILD_DIR)/F_BO4.BIN $(DISK_DIR)/BOSS/BO4/F_BO4.BIN
	cp $(BUILD_DIR)/RBO3.BIN $(DISK_DIR)/BOSS/RBO3/RBO3.BIN
	cp $(BUILD_DIR)/F_RBO3.BIN $(DISK_DIR)/BOSS/RBO3/F_RBO3.BIN
	cp $(BUILD_DIR)/TT_000.BIN $(DISK_DIR)/SERVANT/TT_000.BIN
	cp $(BUILD_DIR)/TT_001.BIN $(DISK_DIR)/SERVANT/TT_001.BIN
	cp $(BUILD_DIR)/TT_002.BIN $(DISK_DIR)/SERVANT/TT_002.BIN
	cp $(BUILD_DIR)/TT_003.BIN $(DISK_DIR)/SERVANT/TT_003.BIN
	cp $(BUILD_DIR)/TT_004.BIN $(DISK_DIR)/SERVANT/TT_004.BIN
disk: disk_prepare
	$(SOTNDISK) make build/sotn.$(VERSION).cue $(DISK_DIR) $(CONFIG_DIR)/disk.us.lba
disk_debug: disk_prepare
	cd tools/sotn-debugmodule && make
	cp $(BUILD_DIR)/../sotn-debugmodule.bin $(DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make build/sotn.$(VERSION).cue $(DISK_DIR) $(CONFIG_DIR)/disk.us.lba

# put this here as both PSX HD and PSP use it
extract_disk_psp%:
	mkdir -p disks/psp$*
	7z x -y disks/sotn.psp$*.iso -odisks/psp$*/
test:
	$(PYTHON) tools/symbols_test.py

function-finder:
	# TODO: make sure graphviz is installed
	$(MAKE) force_symbols
	$(MAKE) force_extract
	$(PYTHON) tools/analyze_calls.py
	git clean -fdx asm/
	git checkout config/
	rm -f build/us/main.ld
	rm -rf build/us/weapon.ld
	$(MAKE) -j extract
	$(PYTHON) tools/function_finder/function_finder_psx.py --use-call-trees > gh-duplicates/functions.md
	rm -rf gh-duplicates/function_calls || true
	mv function_calls gh-duplicates/
	mv function_graphs.md gh-duplicates/

duplicates-report:
	$(MAKE) force_symbols
	$(MAKE) force_extract
	cd tools/dups; \
	    cargo run --release -- \
            --threshold .90 \
            --output-file ../../gh-duplicates/duplicates.txt
			
python-dependencies:
	# the python setup cannot depend on the virtualenv
	# because it may not be set up yet
	[ -d $(VENV_PATH) ] || python3 -m venv $(VENV_PATH)
	pip install -r $(TOOLS_DIR)/requirements-python.txt

update-dependencies: ##@ update tools and internal dependencies
update-dependencies: $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(MASPSX_APP) $(GO) $(ALLEGREX_AS) python-dependencies
	rm $(SOTNDISK) && make $(SOTNDISK) || true
	rm $(SOTNASSETS) && make $(SOTNASSETS) || true
	git clean -fd bin/

bin/%: bin/%.tar.gz
	sha256sum --check $<.sha256
	cd bin && tar -xzf ../$<
	rm $<
	touch $@
bin/%.tar.gz: bin/%.tar.gz.sha256
	wget -O $@ https://github.com/Xeeynamo/sotn-decomp/releases/download/cc1-psx-26/$*.tar.gz
$(ASMDIFFER_APP):
	git submodule init $(ASMDIFFER_DIR)
	git submodule update $(ASMDIFFER_DIR)
$(M2CTX_APP):
	curl -o $@ https://raw.githubusercontent.com/ethteck/m2ctx/main/m2ctx.py
$(M2C_APP):
	git submodule init $(M2C_DIR)
	git submodule update $(M2C_DIR)
	$(PYTHON) -m pip install --upgrade pycparser
$(MASPSX_APP):
	git submodule init $(MASPSX_DIR)
	git submodule update $(MASPSX_DIR)
$(GO):
	curl -L -o go1.22.4.linux-amd64.tar.gz https://go.dev/dl/go1.22.4.linux-amd64.tar.gz
	tar -C $(HOME) -xzf go1.22.4.linux-amd64.tar.gz
	rm go1.22.4.linux-amd64.tar.gz
$(SOTNDISK): $(GO) $(SOTNDISK_SOURCES)
	cd tools/sotn-disk; $(GO) install
$(SOTNASSETS): $(GO) $(SOTNASSETS_SOURCES)
	cd tools/sotn-assets; $(GO) install

# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	./tools/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.json.o: $(ASSETS_DIR)/dra/%.json
	./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.json.o: $(ASSETS_DIR)/ric/%.json
	./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	mkdir -p $(dir $@)
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.gfxbin.o: $(ASSETS_DIR)/%.gfxbin
	mkdir -p $(dir $@)
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.palbin.o: $(ASSETS_DIR)/%.palbin
	mkdir -p $(dir $@)
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.dec.o: $(ASSETS_DIR)/%.dec
# for now '.dec' files are ignored
	touch $@
$(BUILD_DIR)/$(ASSETS_DIR)/%.png.o: $(ASSETS_DIR)/%.png
	touch $@

SHELL = /bin/bash -e -o pipefail

##@
##@ Disc Dumping Targets
##@

dump_disk: ##@ dump a physical game disk
dump_disk: dump_disk_$(VERSION)
dump_disk_eu: dump_disk_cd
dump_disk_hk: dump_disk_cd
dump_disk_jp10: dump_disk_cd
dump_disk_jp11: dump_disk_cd
dump_disk_jp: dump_disk_cd
dump_disk_saturn: dump_disk_cd
dump_disk_us: dump_disk_cd
dump_disk_usproto: dump_disk_cd
dump_disk_psp%: dump_disk_not_supported
dump_disk_xbla%: dump_disk_not_supported
dump_disk_cd: disks/sotn.$(VERSION).cue
dump_disk_not_supported:
	@echo "Automated dumping of $(VERSION) is not supported" >&2 && exit 1
disks/sotn.%.bin disks/sotn.%.cue:
	@( which -s cdrdao && which -s toc2cue ) || (echo "cdrdao(1) and toc2cue(1) must be installed" && exit 1 )
	cd disks && \
        DEVICE="$(shell cdrdao scanbus 2>&1 | grep -vi cdrdao | head -n1 | sed 's/ : [^:]*$$//g')" && \
        cdrdao read-cd \
            --read-raw \
            --datafile sotn.$*.bin \
            --device "$$DEVICE" \
            --driver generic-mmc-raw \
            sotn.$*.toc && \
        toc2cue sotn.$*.toc sotn.$*.cue && \
        rm sotn.$*.toc

.PHONY: all clean patch check build expected
.PHONY: format ff format-src format-tools format-symbols
.PHONY: main dra ric weapon
.PHONY: cen chi dre lib mad no0 no1 no3 no4 np3 nz0 st0 wrp rwrp
.PHONY: mar bo4 rbo3
.PHONY: tt_000 tt_001 tt_002 tt_003 tt_004
.PHONY: %_dirs
.PHONY: extract extract_%
.PHONY: update-dependencies python-dendencies
.PHONY: dump_disk dump_disk_%
