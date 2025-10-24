.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all

### Begin new header ###
PHONY_TARGETS := # Empty variable
MUFFLED_TARGETS := # Empty variable

VERSION		?= us# Only when env not set
VENV_DIR	?= .venv# Can be overriden with env
comma		:= ,# For escaping a literal comma
muffle 		:= $(if $(DEBUG),,@)# Allows DEBUG to unmuffle targets which can't use .SILENT

# Utility functions
rwildcard	= $(subst //,/,$(foreach dir,$(wildcard $(1:=/*)),$(call rwildcard,$(dir),$(2)) $(filter $(subst *,%,$(2)),$(dir))))
wget		= wget -a wget-$(or $(3),$(2),$(1)).log $(if $(2),-O $(2) )$(1)

# System related variables
OS 				:= $(subst Darwin,macOS,$(shell uname -s))
SYSTEM_PYTHON	:= $(or $(shell which python),/usr/bin/python3)# Only used for installing venv
PYTHON_BIN		:= $(or $(realpath $(VENV_DIR)/bin/))
PYTHON          := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)python3# This is slightly redundant to handle the slash
PIP			 	:= $(VENV_DIR)/bin/pip3# Pip will always use venv
BASH			:= $(or $(shell which bash),/usr/bin/bash)
BASH_FLAGS	  	:= -e -o pipefail
SHELL 			:= $(BASH) $(BASH_FLAGS)

# Directories
BIN_DIR			:= bin
ASM_DIR         := asm/$(VERSION)
SRC_DIR         := src
INCLUDE_DIR     := include
ASSETS_DIR      := assets
CONFIG_DIR      := config
TOOLS_DIR       := tools
BUILD_DIR       := build/$(VERSION)
REPORTS_DIR     := $(BUILD_DIR)/reports
PY_TOOLS_DIRS	:= $(TOOLS_DIR)/ $(addprefix $(TOOLS_DIR)/,splat_ext/ split_jpt_yaml/ sotn_permuter/permuter_loader)
RETAIL_DISK_DIR := disks
EXTRACTED_DISK_DIR := $(RETAIL_DISK_DIR)/$(VERSION)
BUILD_DISK_DIR  := $(BUILD_DIR)/disk

# Files
CHECK_FILES 	:= $(shell cut -d' ' -f3 $(CONFIG_DIR)/check.$(VERSION).sha)
ST_ASSETS		:= D_801*.bin *.gfxbin *.palbin cutscene_*.bin
CLEAN_FILES		:= $(ASSETS_DIR) $(ASM_DIR) $(BUILD_DIR) $(SRC_DIR)/weapon $(CONFIG_DIR)/*$(VERSION)* function_calls sotn_calltree.txt
FORMAT_SRC_IGNORE	:= $(call rwildcard,src/pc/3rd/,*)
FORMAT_SRC_FILES	:= $(filter-out $(FORMAT_SRC_IGNORE),$(call rwildcard,$(SRC_DIR)/ $(INCLUDE_DIR)/,*.c *.h))
FORMAT_SYMBOLS_IGNORE	:= $(addprefix $(CONFIG_DIR)/,splat.us.weapon.yaml assets.hd.yaml assets.us.yaml)
FORMAT_SYMBOLS_FILES	:= $(filter-out $(FORMAT_SYMBOLS_IGNORE),$(wildcard $(CONFIG_DIR)/*.yaml))

# Toolchain
CROSS           := mipsel-linux-gnu-
LD              := $(CROSS)ld
OBJCOPY         := $(CROSS)objcopy
ALLEGREX 		:= $(BIN_DIR)/allegrex-as
WIBO            := $(BIN_DIR)/wibo
MWCCPSP         := $(BIN_DIR)/mwccpsp.exe
CYGNUS			:= $(BIN_DIR)/cygnus-2.7-96Q3-bin

# Symbols
BASE_SYMBOLS	 = $(CONFIG_DIR)/symbols.$(if $(filter mad,$(1)),beta,$(VERSION)).txt
UNDEFINED_SYMS 	 = $(CONFIG_DIR)/undefined_syms.$(if $(filter stmad,$(1)),beta,$(VERSION)).txt
AUTO_UNDEFINED	 = TYPE_auto$(if $(filter-out stmad,$(1)),.$(VERSION)).$(1).txt

# Other tooling
BLACK			:= $(and $(PYTHON_BIN),$(PYTHON_BIN)/)black
SPLAT           := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)splat split
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py
SHASUM          := shasum
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
CLANG			:= $(BIN_DIR)/clang-format
GOPATH          := $(HOME)/go
GO              := $(GOPATH)/bin/go
SOTNLINT		:= cargo run --release --manifest-path $(TOOLS_DIR)/lints/sotn-lint/Cargo.toml $(SRC_DIR)/
DUPS_THRESHOLD  ?= .90
DUPS			:= cd $(TOOLS_DIR)/dups; cargo run --release -- --threshold $(DUPS_THRESHOLD) --output-file ../../$(REPORTS_DIR)/duplicates.txt
MIPSMATCH_APP   := $(BIN_DIR)/mipsmatch
SOTNSTR_APP     := $(TOOLS_DIR)/sotn_str/target/release/sotn_str
ASMDIFFER_APP	:= $(TOOLS_DIR)/asm-differ/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2C_APP         := $(TOOLS_DIR)/m2c/m2c.py
PERMUTER_APP	:= $(TOOLS_DIR)/decomp-permuter
MASPSX_APP      := $(TOOLS_DIR)/maspsx/maspsx.py
MWCCGAP_APP     := $(TOOLS_DIR)/mwccgap/mwccgap.py
DOSEMU_APP		:= $(or $(shell which dosemu),/usr/bin/dosemu)
SATURN_SPLITTER_DIR := $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
SOTNDISK        := bin/sotn-disk
SOTNASSETS      := bin/sotn-assets

# Directories
DISK_DIR        := $(BUILD_DIR)/${VERSION}/disk

# Symbols
MAIN_TARGET     := $(BUILD_DIR)/main

MIPSMATCH_DIR   := $(TOOLS_DIR)/mipsmatch
ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2CTX           := $(PYTHON) $(M2CTX_APP)
M2C_DIR         := $(TOOLS_DIR)/m2c
M2C_APP         := $(M2C_DIR)/m2c.py
M2C             := $(PYTHON) $(M2C_APP)
M2C_ARGS        := -P 4
MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py

DEPENDENCIES	= $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(MASPSX_APP) $(GO) $(MIPSMATCH_APP) python-dependencies

SOTNDISK_SOURCES   := $(shell find tools/sotn-disk -name '*.go')
SOTNASSETS_SOURCES := $(shell find tools/sotn-assets -name '*.go')

ifeq ($(VERSION),saturn)
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
all: build_all check

.PHONY: extract_assets
extract_assets:
extract_assets: $(SOTNASSETS)
	$(SOTNASSETS) extract config/assets.$(VERSION).yaml
.PHONY: build_assets
build_assets:
build_assets: $(SOTNASSETS)
	$(SOTNASSETS) build config/assets.$(VERSION).yaml
.PHONY: extract
extract: ##@ extract assets
extract: extract_$(VERSION)
extract_us: extract_assets
extract_hd: extract_assets
extract_pspeu: extract_assets

.PHONY: build
build: ##@ build game files
build: build_$(VERSION)
build_us: bin/cc1-psx-26 $(MASPSX_APP) $(SOTNASSETS)
	VERSION=us .venv/bin/python3 tools/builds/gen.py
	ninja
build_hd: bin/cc1-psx-26 $(MASPSX_APP) $(SOTNASSETS)
	VERSION=hd .venv/bin/python3 tools/builds/gen.py
	ninja
build_pspeu: $(SOTNSTR_APP) $(SOTNASSETS) $(ALLEGREX) $(MWCCPSP) $(MWCCGAP_APP) $(ALLEGREX) | $(VENV_DIR)/bin
	VERSION=pspeu .venv/bin/python3 tools/builds/gen.py
	ninja
.PHONY: build_all
build_all: $(MASPSX_APP) $(SOTNSTR_APP) $(SOTNASSETS) $(ALLEGREX) $(MWCCPSP) $(MWCCGAP_APP) $(ALLEGREX) | $(VENV_DIR)/bin
	$(PYTHON) tools/builds/gen.py
	ninja

.PHONY: clean clean_asm
clean_asm:
	git clean -fdx $(ASM_DIR)
clean: ##@ clean extracted files, assets, and build artifacts
clean: clean_asm
	git clean -fdx assets/
	git clean -fdx build/
	git clean -fdx src/**/gen/
	git clean -fdx config/
	git clean -fdx function_calls/
	git clean -fdx sotn_calltree.txt

##@
##@ Misc Targets
##@

# this help target will find targets which are followed by a comment beginning with '#' '#' '@' and
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


.PHONY: lint format-sotn-lint
lint: format-sotn-lint
format-sotn-lint:
	$(SOTNLINT) || ( echo lint failed 1>&2 && exit 1 )

.PHONY: format-src
format-src: bin/clang-format format-sotn-lint
	@# find explainer:
	@#    find $(SRC_DIR) $(INCLUDE_DIR)                      : look in src and include
	@#    -type d \( -name 3rd -o -name CMakeFiles \) -prune  : if an entry is both a directory and 3rd or CMakeFiles
	@#                                                          ignore it and don't traverse it
	@#    -o \( -type f \( -name '*.h' -o -name '*.c' \) \)   : or if an entry is a file and named *.h or *.c, include it
	@#    -print0                                             : print only the matching entries, delimit by NULL to
	@#                                                          ensure files with characters xargs uses as delimiters are
	@#                                                          properly handled
	find $(SRC_DIR) $(INCLUDE_DIR) mods \
        -type d \( -name 3rd -o -name CMakeFiles -o -name gen \) -prune \
        -o \( -type f \( -name '*.c' -o -name '*.h' \) \) \
        -print0 \
        | xargs -0 -n10 -P$$(nproc) bin/clang-format -i

.PHONY: format-tools
format-tools:
	$(BLACK) tools/*.py
	$(BLACK) tools/builds/gen.py
	$(BLACK) tools/splat_ext/*.py
	$(BLACK) tools/split_jpt_yaml/*.py
	$(BLACK) tools/sotn_permuter/permuter_loader.py
	$(BLACK) diff_settings.py
	$(BLACK) tools/function_finder/*.py

.PHONY: format-symbols format-symbols-%
format-symbols-us-sort:
	VERSION=us $(PYTHON) ./tools/symbols.py sort
format-symbols-us-%: format-symbols-us-sort
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.$*.yaml
format-symbols-us: $(patsubst config/splat.us.%.yaml,format-symbols-us-%,$(wildcard config/splat.us.*.yaml))
format-symbols-hd-sort:
	VERSION=hd $(PYTHON) ./tools/symbols.py sort
format-symbols-hd-%: format-symbols-hd-sort
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.hd.$*.yaml
format-symbols-hd: $(patsubst config/splat.hd.%.yaml,format-symbols-hd-%,$(wildcard config/splat.hd.*.yaml))
format-symbols-pspeu-sort:
	VERSION=pspeu $(PYTHON) ./tools/symbols.py sort
format-symbols-pspeu-%: format-symbols-pspeu-sort
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.pspeu.$*.yaml
format-symbols-pspeu: $(patsubst config/splat.pspeu.%.yaml,format-symbols-pspeu-%,$(wildcard config/splat.pspeu.*.yaml))
format-symbols: format-symbols-us format-symbols-hd format-symbols-pspeu

format-license:
	find src/ mods/ | grep -E '\.c$$|\.h$$' | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | $(PYTHON) ./tools/lint-license.py - AGPL-3.0-or-later
	find src/main/psxsdk | grep -E '\.c$$|\.h$$' | $(PYTHON) ./tools/lint-license.py - MIT
	$(PYTHON) ./tools/lint-license.py include/game.h AGPL-3.0-or-later
	$(PYTHON) ./tools/lint-license.py include/entity.h AGPL-3.0-or-later
	$(PYTHON) ./tools/lint-license.py include/items.h AGPL-3.0-or-later
	$(PYTHON) ./tools/lint-license.py include/lba.h AGPL-3.0-or-later
	$(PYTHON) ./tools/lint-license.py include/memcard.h AGPL-3.0-or-later

# fast-format
.PHONY: ff
ff: MAKEFLAGS += --jobs
ff:
	$(MAKE) format

.PHONY: expected
expected: build
	mkdir -p expected/build
	rm -rf expected/build/$(VERSION)
	cp -r build/$(VERSION) expected/build/

# Force to extract all the assembly code regardless if a function is already decompiled
force_extract:
	find $(BUILD_DIR) -type f -name "*.ld" -delete
	$(MAKE) extract -j
	$(MAKE) -j

.PHONY: force_symbols
force_symbols: ##@ Extract a full list of symbols from a successful build
force_symbols: clean_asm
	FORCE_SYMBOLS= $(PYTHON) tools/builds/gen.py $(BUILD_DIR)/dynsyms.ninja
	# only force symbols for overlays that are built. weapons are excluded with `-maxdepth 1`
	linker_scripts="$$(find $(BUILD_DIR) -maxdepth 1 -type f -name '*.elf' | sed 's/\.elf/\.ld/')" && \
	   if [[ -n $$linker_scripts ]]; then \
		   xargs rm -f <<< "$$linker_scripts" && \
		   xargs ninja -j0 -f $(BUILD_DIR)/dynsyms.ninja <<< "$$linker_scripts" ; \
	   fi

context: ##@ create a context for decomp.me. Set the SOURCE variable prior to calling this target
	VERSION=$(VERSION) $(M2CTX) $(SOURCE)
	@echo ctx.c has been updated.

# Targets to extract the data from the disk image
extract-disk: $(EXTRACTED_DISK_DIR)
$(EXTRACTED_DISK_DIR:$(VERSION)=us): | $(SOTNDISK)
	$(SOTNDISK) extract $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)
$(EXTRACTED_DISK_DIR:$(VERSION)=pspeu) $(EXTRACTED_DISK_DIR:$(VERSION)=hd):
	mkdir -p $(EXTRACTED_DISK_DIR)
	7z x -y $(RETAIL_DISK_DIR)/sotn.pspeu.iso -o$(EXTRACTED_DISK_DIR)
$(EXTRACTED_DISK_DIR:$(VERSION)=saturn):
	bchunk $(RETAIL_DISK_DIR)/sotn.$(VERSION).bin $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(RETAIL_DISK_DIR)/sotn.$(VERSION).iso
	-7z x $(RETAIL_DISK_DIR)/sotn.$(VERSION).iso01.iso -o$(EXTRACTED_DISK_DIR)

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
	cp $(BUILD_DIR)/NO2.BIN $(DISK_DIR)/ST/NO2/NO2.BIN
	cp $(BUILD_DIR)/F_NO2.BIN $(DISK_DIR)/ST/NO2/F_NO2.BIN
	cp $(BUILD_DIR)/NO3.BIN $(DISK_DIR)/ST/NO3/NO3.BIN
	cp $(BUILD_DIR)/F_NO3.BIN $(DISK_DIR)/ST/NO3/F_NO3.BIN
	cp $(BUILD_DIR)/NO4.BIN $(DISK_DIR)/ST/NO4/NO4.BIN
	cp $(BUILD_DIR)/F_NO4.BIN $(DISK_DIR)/ST/NO4/F_NO4.BIN
	cp $(BUILD_DIR)/NP3.BIN $(DISK_DIR)/ST/NP3/NP3.BIN
	cp $(BUILD_DIR)/F_NP3.BIN $(DISK_DIR)/ST/NP3/F_NP3.BIN
	cp $(BUILD_DIR)/NZ0.BIN $(DISK_DIR)/ST/NZ0/NZ0.BIN
	cp $(BUILD_DIR)/F_NZ0.BIN $(DISK_DIR)/ST/NZ0/F_NZ0.BIN
	cp $(BUILD_DIR)/SEL.BIN $(DISK_DIR)/ST/SEL/SEL.BIN
	cp $(BUILD_DIR)/ST0.BIN $(DISK_DIR)/ST/ST0/ST0.BIN
	cp $(BUILD_DIR)/F_ST0.BIN $(DISK_DIR)/ST/ST0/F_ST0.BIN
	cp $(BUILD_DIR)/TOP.BIN $(DISK_DIR)/ST/TOP/TOP.BIN
	cp $(BUILD_DIR)/F_TOP.BIN $(DISK_DIR)/ST/TOP/F_TOP.BIN
	cp $(BUILD_DIR)/WRP.BIN $(DISK_DIR)/ST/WRP/WRP.BIN
	cp $(BUILD_DIR)/F_WRP.BIN $(DISK_DIR)/ST/WRP/F_WRP.BIN
	cp $(BUILD_DIR)/RTOP.BIN $(DISK_DIR)/ST/RTOP/RTOP.BIN
	cp $(BUILD_DIR)/F_RTOP.BIN $(DISK_DIR)/ST/RTOP/F_RTOP.BIN
	cp $(BUILD_DIR)/RWRP.BIN $(DISK_DIR)/ST/RWRP/RWRP.BIN
	cp $(BUILD_DIR)/F_RWRP.BIN $(DISK_DIR)/ST/RWRP/F_RWRP.BIN
	cp $(BUILD_DIR)/MAR.BIN $(DISK_DIR)/BOSS/MAR/MAR.BIN
	cp $(BUILD_DIR)/F_MAR.BIN $(DISK_DIR)/BOSS/MAR/F_MAR.BIN
	cp $(BUILD_DIR)/BO4.BIN $(DISK_DIR)/BOSS/BO4/BO4.BIN
	cp $(BUILD_DIR)/F_BO4.BIN $(DISK_DIR)/BOSS/BO4/F_BO4.BIN
	cp $(BUILD_DIR)/RBO3.BIN $(DISK_DIR)/BOSS/RBO3/RBO3.BIN
	cp $(BUILD_DIR)/F_RBO3.BIN $(DISK_DIR)/BOSS/RBO3/F_RBO3.BIN
	cp $(BUILD_DIR)/RBO5.BIN $(DISK_DIR)/BOSS/RBO5/RBO5.BIN
	cp $(BUILD_DIR)/F_RBO5.BIN $(DISK_DIR)/BOSS/RBO5/F_RBO5.BIN
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
extract_disk_us: extract_disk_psxus
extract_disk_hd: extract_disk_pspeu
extract_disk_psx%: $(SOTNDISK)
	$(SOTNDISK) extract disks/sotn.$*.cue disks/$* > /dev/null
extract_disk_psp%:
	mkdir -p disks/psp$*
	7z x -y disks/sotn.psp$*.iso -odisks/psp$*/
test:
	$(PYTHON) tools/symbols_test.py

.PHONY: python-dependencies
python-dependencies: $(VENV_DIR)
	$(PIP) install -r $(TOOLS_DIR)/requirements-python.txt

$(VENV_DIR):
	$(SYSTEM_PYTHON) -m venv $(VENV_DIR)

.PHONY: update-dependencies
update-dependencies: ##@ update tools and internal dependencies
update-dependencies: $(DEPENDENCIES) dependencies_pspeu
	rm $(SOTNDISK) && make $(SOTNDISK) || true
	rm $(SOTNASSETS) && make $(SOTNASSETS) || true
	cargo build --release --manifest-path ./tools/sotn_str/Cargo.toml
	git clean -fd bin/

dependencies_pspeu: $(ALLEGREX) $(MWCCGAP_APP) $(MWCCPSP)
$(MWCCGAP_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(MWCCGAP_APP))
$(WIBO):
	curl -sSfL -o $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	$(muffle)sha256sum --check $(WIBO).sha256; chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) $(BIN_DIR)/mwccpsp_219

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

$(MIPSMATCH_DIR)/target/release/mipsmatch: $(MIPSMATCH_DIR) $(shell find $(MIPSMATCH_DIR)/src $(MIPSMATCH_DIR)/Cargo.* -type f)
	git submodule init $(MIPSMATCH_DIR)
	git submodule update $(MIPSMATCH_DIR)
	cd $(MIPSMATCH_DIR) ; \
	    cargo build --release
$(MIPSMATCH_APP): $(MIPSMATCH_DIR)/target/release/mipsmatch
	cp $< $@
$(GO):
	curl -L -o go1.22.4.linux-amd64.tar.gz https://go.dev/dl/go1.24.4.linux-amd64.tar.gz
	tar -C $(HOME) -xzf go1.22.4.linux-amd64.tar.gz
	rm go1.22.4.linux-amd64.tar.gz
$(SOTNDISK): $(GO) $(SOTNDISK_SOURCES)
	$(GO) build -C tools/sotn-disk -o ../../$@ .
$(SOTNASSETS): $(GO) $(SOTNASSETS_SOURCES)
	$(GO) build -C tools/sotn-assets -o ../../$@ .

build/$(VERSION)/src/%.o: src/%
	ninja $@


##@
##@ Reporting Targets
##@

.PHONY: reports prepare-reports
reports: duplicates-report function-finder
prepare-reports: build $(REPORTS_DIR)
	$(MAKE) force_symbols -j
	$(PYTHON) tools/function_finder/fix_matchings.py

function-finder: ##@ generates lists of files, their decomp status, and call graphs
function-finder: prepare-reports
	# TODO: make sure graphviz is installed
	$(PYTHON) tools/function_finder/function_finder_psx.py > $(REPORTS_DIR)/functions.md

$(REPORTS_DIR):
	mkdir -p $(REPORTS_DIR)

.PHONY: duplicates-report
duplicates-report: ##@ generate a report of duplicate functions
duplicates-report: $(REPORTS_DIR)/duplicates.txt
$(REPORTS_DIR)/duplicates.txt: prepare-reports
	$(DUPS)


##@
##@ Disc Dumping Targets
##@

.PHONY: dump_disk%
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

# .PHONY and .SILENT group
# Putting this in a separate section because if it is included with the targets as I'd prefer, it becomes very cluttered and harder to read.
# These lists can be added to at any point since adding the lists to the actual .PHONY and .SILENT targets is the final action and order does not matter.
# I'd prefer assigning to .PHONY and .SILENT directly without using the list, but the list allows us to have a target that displays it to the user for debugging.
# They are grouped in the general order you will find the targets in the file.
PHONY: # Since .PHONY reads % as a literal %, we need this target as a prereq to treat pattern targets as .PHONY
PHONY_TARGETS += all all-clean build-and-check clean $(addprefix CLEAN_,$(CLEAN_FILES)) extract build patch check expected
PHONY_TARGETS += dump-disk $(addprefix dump-disk_,eu hk jp10 jp11 saturn us usproto) extract-disk disk disk-prepare disk-debug
PHONY_TARGETS += format-src format-src.run $(addprefix FORMAT_,$(FORMAT_SRC_FILES)) format-tools $(addprefix FORMAT_,$(PY_TOOLS_DIRS))
PHONY_TARGETS += format-symbols format-symbols.run $(addprefix format-symbols_,us hd pspeu saturn) $(addprefix FORMAT_,$(FORMAT_SYMBOLS_FILES)) format-license
PHONY_TARGETS += force-symbols $(addprefix FORCE_,$(FORCE_SYMBOLS)) force-extract context function-finder duplicates-report
PHONY_TARGETS += git-submodules update-dependencies update-dependencies-all $(addprefix dependencies_,us pspeu hd saturn) requirements-python graphviz
PHONY_TARGETS += help get-debug get-phony get-silent
MUFFLED_TARGETS += $(PHONY_TARGETS) $(MASPSX_APP) $(MWCCGAP_APP) $(MWCCPSP) $(SATURN_SPLITTER_DIR) $(SATURN_SPLITTER_APP) $(EXTRACTED_DISK_DIR)
MUFFLED_TARGETS += $(DOSEMU_APP) $(ASMDIFFER) $(dir $(M2C_APP)) $(M2C_APP) $(PERMUTER_APP) $(SOTNDISK) $(SOTNASSETS) $(VENV_DIR) $(VENV_DIR)/bin
.PHONY: $(PHONY_TARGETS)
# Specifying .SILENT in this manner allows us to set the DEBUG environment variable and display everything for debugging
#$(DEBUG).SILENT: $(MUFFLED_TARGETS)
# These are walls of text, so they're redirected to files instead of stdout for debugging
get-debug: get-phony get-silent
get-phony:
	echo ".PHONY:" > make.phony.targets
	$(foreach target,$(PHONY_TARGETS),echo $(target) >> make.phony.targets;)
get-silent:
	echo ".SILENT:" > make.silent.targets
	$(foreach target,$(MUFFLED_TARGETS),echo $(target) >> make.silent.targets;)
