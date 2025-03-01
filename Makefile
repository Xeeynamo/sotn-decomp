# Make configuration
.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all

# Environment
ifeq ($(VERSION),)
$(info VERSION not defined, defaulting to VERSION=us)
VERSION         ?= us
endif

# Compilers
CROSS           := mipsel-linux-gnu-
LD              := $(CROSS)ld
OBJCOPY         := $(CROSS)objcopy

# Directories
ASM_DIR         := asm/$(VERSION)
BIN_DIR         := bin
SRC_DIR         := src
ASSETS_DIR      := assets
INCLUDE_DIR     := include
BUILD_DIR       := build/$(VERSION)
EXPECTED_DIR	:= expected/$(BUILD_DIR)
DISK_DIR        := $(BUILD_DIR)/${VERSION}/disk
CONFIG_DIR      := config
TOOLS_DIR       := tools

# Symbols
MAIN_TARGET     := $(BUILD_DIR)/main
BASE_SYMBOLS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

# Tooling
SHELL 			 = /usr/bin/bash -e -o pipefail
VENV_DIR       	?= .venv
PYTHON_BIN		:= $(VENV_DIR)/bin
PYTHON          := $(PYTHON_BIN)/python3
PIP			 	:= $(PYTHON_BIN)/pip3
INLINE_PYTHON	:= $(PYTHON) -c
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
export PATH     := $(VENV_DIR)/bin:$(PATH)

# Dependencies
DEPENDENCIES	= $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(MASPSX_APP) $(GO) python-dependencies

SOTNDISK_SOURCES   := $(shell find $(TOOLS_DIR)/sotn-disk -name '*.go')
SOTNASSETS_SOURCES := $(shell find $(TOOLS_DIR)/sotn-assets -name '*.go')

CHECK_FILES := $(shell cut -d' ' -f3 $(CONFIG_DIR)/check.$(VERSION).sha)

# Functions
ROOT		:= /
ifneq ($(filter $(VERSION),us hd),)
ASM_SUBDIRS := $(ROOT) /data /psxsdk /handwritten
SRC_SUBDIRS := $(ROOT) /psxsdk
else ifeq ($(VERSION),pspeu)
ASM_SUBDIRS := $(ROOT) /data
SRC_SUBDIRS := $(ROOT)
endif
ST_ASM_SUBDIRS := $(ROOT) /data
ST_ASSETS = /D_801*.bin /*.gfxbin /*.palbin /cutscene_*.bin

define list_src_files
	$(foreach dir,$(addprefix $(ASM_DIR)/$(1), $(ASM_SUBDIRS)),$(wildcard $(dir)/*.s))
	$(foreach dir,$(addprefix $(SRC_DIR)/$(1), $(SRC_SUBDIRS)),$(wildcard $(dir)/*.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/*))
endef
define list_st_src_files
	$(foreach dir,$(addprefix $(ASM_DIR)/$(1), $(ST_ASM_SUBDIRS)),$(wildcard $(dir)/*.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/*.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(addprefix $(dir), $(ST_ASSETS))))
endef
define list_shared_src_files
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/*.c))
endef
define list_o_files
	$(foreach file,$(call list$(2)_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

# leverages MWCC ability to compile data and text as separate sections to allow
# LD using --gc-sections and remove all the symbols that are unreferenced.
# symexport.*.txt is used to enforce a specific symbol and all its dependencies
# to be used. Refer to *.map to know which sections are being discarded by LD.
# Use nm to retrieve the symbol name out of a object file such as the mwo_header.
ifeq ($(VERSION),pspeu)
GC_SECTIONS := --gc-sections
SYM_EXPORT 	= -T $(CONFIG_DIR)/symexport.$(VERSION).$(1).txt
endif

define link
	$(LD) $(LD_FLAGS) -o $(2) \
		$(GC_SECTIONS) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(1).ld \
		$(SYM_EXPORT) \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).$(1).txt
endef

ifneq ($(filter $(VERSION),us hd),) # Both us and hd versions use the PSX platform
include Makefile.psx.mk
else ifeq ($(VERSION),pspeu)
include Makefile.psp.mk
else ifeq ($(VERSION),saturn)
include Makefile.saturn.mk
endif

##@ Variables
##@
##@     VERSION              the game version to build (us, hd, pspeu, saturn, pc) (Default: us)
##@
##@ Primary Targets
##@

.PHONY: all
all: ##@ (Default) build and check
all: build check

.PHONY: extract 
extract: ##@ split game files into assets and assembly
extract: extract_$(VERSION)

.PHONY: build 
build: ##@ build game files
build: build_$(VERSION)

.PHONY: clean
clean: ##@ clean extracted files, assets, and build artifacts
	git clean -fdx assets/
	git clean -fdx asm/$(VERSION)/
	git clean -fdx build/$(VERSION)/
	git clean -fdx $(SRC_DIR)/weapon
	git clean -fdx $(CONFIG_DIR)/*$(VERSION)*
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

.PHONY: format
format: ##@ Format source code, clean symbols, other linting
format: format-src format-tools format-symbols format-license

.PHONY: format-src
format-src: $(BIN_DIR)/clang-format
	cargo run --release --manifest-path $(TOOLS_DIR)/lints/sotn-lint/Cargo.toml ./src
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
        | xargs -0 -n10 -P$$(nproc) $(BIN_DIR)/clang-format -i

.PHONY: format-tools
format-tools:
	black $(TOOLS_DIR)/*.py
	black $(TOOLS_DIR)/splat_ext/*.py
	black $(TOOLS_DIR)/split_jpt_yaml/*.py

ORPHAN_EXCLUSIONS 	:= splat.us.weapon assets.hd assets.us
ORPHAN_EXCLUSIONS	:= $(addprefix $(CONFIG_DIR)/, $(addsuffix .yaml, $(ORPHAN_EXCLUSIONS)))
ORPHAN_REMOVALS 	:= $(filter-out $(ORPHAN_EXCLUSIONS), $(wildcard config/*.yaml))

.PHONY: format-symbols
$(DEBUG).SILENT: format-symbols
format-symbols:
	for VERSION in us hd pspeu saturn; do  \
	echo Sorting $$VERSION symbols; 	   \
	$(PYTHON) $(TOOLS_DIR)/symbols.py sort; \
	done
	for FILE in $(ORPHAN_REMOVALS); do     \
	echo Removing orphan symbols from $$FILE; \
	$(TOOLS_DIR)/symbols.py remove-orphans $$FILE; \
	done

$(DEBUG).SILENT: format-license
format-license:
	echo Checking for license line in code files
	find src/ | grep -E '\.c$$|\.h$$' | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | python3 $(TOOLS_DIR)/lint-license.py - AGPL-3.0-or-later
	python3 $(TOOLS_DIR)/lint-license.py include/game.h AGPL-3.0-or-later
	python3 $(TOOLS_DIR)/lint-license.py include/entity.h AGPL-3.0-or-later
	python3 $(TOOLS_DIR)/lint-license.py include/items.h AGPL-3.0-or-later
	python3 $(TOOLS_DIR)/lint-license.py include/lba.h AGPL-3.0-or-later
	python3 $(TOOLS_DIR)/lint-license.py include/memcard.h AGPL-3.0-or-later

# fast-format
.PHONY: ff
ff: MAKEFLAGS += --jobs
ff:
	$(MAKE) format

.PHONY: patch
patch:
	$(DIRT_PATCHER) $(CONFIG_DIR)/dirt.$(VERSION).json

.PHONY: check
check: ##@ compare built files to original game files
check: $(CONFIG_DIR)/check.$(VERSION).sha patch $(CHECK_FILES)
	@$(SHASUM) --check $< | awk 'BEGIN{ FS=": " }; { \
        printf "%s\t[ ", $$1; \
        if ($$2 == "OK") \
            color = 28;   \
        else \
            color = 196;   \
        system("tput setaf " color "; printf " $$2 "; tput sgr0"); \
        printf " ]\n"; \
    }' | column --separator $$'\t' --table

.PHONY: expected
expected: check
	mkdir -p expected/build
	rm -rf expected/build/$(VERSION)
	cp -r build/$(VERSION) expected/build/

# Force to extract all the assembly code regardless if a function is already decompiled
force_extract:
	mv src src_tmp
	rm $(BUILD_DIR)/*.ld
	make extract -j
	rm -rf src/
	mv src_tmp src

force_symbols: ##@ Extract a full list of symbols from a successful build
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/dra.elf > $(CONFIG_DIR)/symbols.us.dra.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/ric.elf > $(CONFIG_DIR)/symbols.us.ric.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stcen.elf > $(CONFIG_DIR)/symbols.us.stcen.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stchi.elf > $(CONFIG_DIR)/symbols.us.stchi.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stdre.elf > $(CONFIG_DIR)/symbols.us.stdre.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stlib.elf > $(CONFIG_DIR)/symbols.us.stlib.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stno0.elf > $(CONFIG_DIR)/symbols.us.stno0.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stno1.elf > $(CONFIG_DIR)/symbols.us.stno1.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stno3.elf > $(CONFIG_DIR)/symbols.us.stno3.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stno4.elf > $(CONFIG_DIR)/symbols.us.stno4.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stnp3.elf > $(CONFIG_DIR)/symbols.us.stnp3.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stnz0.elf > $(CONFIG_DIR)/symbols.us.stnz0.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stsel.elf > $(CONFIG_DIR)/symbols.us.stsel.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stst0.elf > $(CONFIG_DIR)/symbols.us.stst0.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/stwrp.elf > $(CONFIG_DIR)/symbols.us.stwrp.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/strwrp.elf > $(CONFIG_DIR)/symbols.us.strwrp.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/bomar.elf > $(CONFIG_DIR)/symbols.us.bomar.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/bobo4.elf > $(CONFIG_DIR)/symbols.us.bobo4.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/borbo3.elf > $(CONFIG_DIR)/symbols.us.borbo3.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/tt_000.elf > $(CONFIG_DIR)/symbols.us.tt_000.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/tt_001.elf > $(CONFIG_DIR)/symbols.us.tt_001.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/tt_002.elf > $(CONFIG_DIR)/symbols.us.tt_002.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/tt_003.elf > $(CONFIG_DIR)/symbols.us.tt_003.txt
	$(PYTHON) $(TOOLS_DIR)/symbols.py elf build/us/tt_004.elf > $(CONFIG_DIR)/symbols.us.tt_004.txt

context: ##@ create a context for decomp.me. Set the SOURCE variable prior to calling this target
	VERSION=$(VERSION) $(M2CTX) $(SOURCE)
	@echo ctx.c has been updated.

.PHONY: extract_%
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
	cd $(TOOLS_DIR)/sotn-debugmodule && make
	cp $(BUILD_DIR)/../sotn-debugmodule.bin $(DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make build/sotn.$(VERSION).cue $(DISK_DIR) $(CONFIG_DIR)/disk.us.lba

# put this here as both PSX HD and PSP use it
.PHONY: extract_%
extract_disk_psp%:
	mkdir -p disks/psp$*
	7z x -y disks/sotn.psp$*.iso -odisks/psp$*/
test:
	$(PYTHON) $(TOOLS_DIR)/symbols_test.py

function-finder:
	# TODO: make sure graphviz is installed
	$(MAKE) force_symbols
	$(MAKE) force_extract
	$(PYTHON) $(TOOLS_DIR)/analyze_calls.py
	git clean -fdx asm/
	git checkout $(CONFIG_DIR)/
	rm -f build/us/main.ld
	rm -rf build/us/weapon.ld
	$(MAKE) -j extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/function_finder_psx.py --use-call-trees > gh-duplicates/functions.md
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
			
.PHONY: %-dependencies
debian-dependencies:
	sudo apt-get install -y $(cat tools/requirements-debian.txt)
	touch debian-dependencies

python-dependencies: $(VENV_DIR)
	$(PIP) install -r $(TOOLS_DIR)/requirements-python.txt

$(VENV_DIR): debian-dependencies
	python3 -m venv $(VENV_DIR)

update-dependencies: ##@ update tools and internal dependencies
update-dependencies: $(DEPENDENCIES)
	rm $(SOTNDISK) && make $(SOTNDISK) || true
	rm $(SOTNASSETS) && make $(SOTNASSETS) || true
	git clean -fd $(BIN_DIR)/

$(BIN_DIR)/%: $(BIN_DIR)/%.tar.gz
	sha256sum --check $<.sha256
	cd $(BIN_DIR) && tar -xzf ../$<
	rm $<
	touch $@
$(BIN_DIR)/%.tar.gz: $(BIN_DIR)/%.tar.gz.sha256
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
	cd $(TOOLS_DIR)/sotn-disk; $(GO) install
$(SOTNASSETS): $(GO) $(SOTNASSETS_SOURCES)
	cd $(TOOLS_DIR)/sotn-assets; $(GO) install

# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	$(TOOLS_DIR)/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.json.o: $(ASSETS_DIR)/dra/%.json
	$(TOOLS_DIR)/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.json.o: $(ASSETS_DIR)/ric/%.json
	$(TOOLS_DIR)/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
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

##@
##@ Disc Dumping Targets
##@

.PHONY: dump_disk dump_disk_%
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
