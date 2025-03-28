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
echo		= $(if $(and $(QUIET),$(2)),,echo -e "$(subst //,/,$(1))";)# Allows for optional terminal messages
to_upper	= $(shell echo $(1) | tr '[:lower:]' '[:upper:]')
to_lower	= $(shell echo $(1) | tr '[:upper:]' '[:lower:]')
if_version	= $(if $(filter $(1),$(VERSION)),$(2),$(3))
wget		= wget -a wget-$(or $(3),$(2),$(1)).log $(if $(2),-O $(2) )$(1)
# Use $(call get_targets,prefixed) when stages and bosses need to be prefixed
get_targets = $(GAME) $(addprefix $(if $(1),st),$(STAGES)) $(addprefix $(if $(1),bo),$(BOSSES)) $(SERVANTS)

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
ASM_SUBDIRS 	:= data/ $(call if_version,us hd,psxsdk/ handwritten/)
SRC_DIR         := src
SRC_SUBDIRS 	:= $(call if_version,us hd,psxsdk/)
INCLUDE_DIR     := include
ASSETS_DIR      := assets
CONFIG_DIR      := config
TOOLS_DIR       := tools
BUILD_DIR       := build/$(VERSION)
PY_TOOLS_DIRS	:= $(TOOLS_DIR)/ $(addprefix $(TOOLS_DIR)/,splat_ext/ split_jpt_yaml/ sotn_str/ sotn_permuter/permuter_loader)
RETAIL_DISK_DIR := disks
EXTRACTED_DISK_DIR := $(RETAIL_DISK_DIR)/$(VERSION)
BUILD_DISK_DIR  := $(BUILD_DIR)/disk

# Files
UNDEFINED_SYMS 	 = undefined_syms.$(if $(filter stmad,$(1)),beta,$(VERSION)).txt
AUTO_UNDEFINED	 = TYPE_auto$(if $(filter-out stmad,$(1)),.$(VERSION)).$(1).txt
CHECK_FILES 	:= $(shell cut -d' ' -f3 $(CONFIG_DIR)/check.$(VERSION).sha)
ST_ASSETS		:= D_801*.bin *.gfxbin *.palbin cutscene_*.bin
CLEAN_FILES		:= $(ASSETS_DIR) $(ASM_DIR) $(BUILD_DIR) $(SRC_DIR)/weapon $(CONFIG_DIR)/*$(VERSION)* function_calls sotn_calltree.txt
FORMAT_SRC_IGNORE	:= $(call rwildcard,src/pc/3rd/,*)
FORMAT_SRC_FILES	:= $(filter-out $(FORMAT_SRC_IGNORE),$(call rwildcard,$(SRC_DIR)/ $(INCLUDE_DIR)/,*.c *.h))
FORMAT_SYMBOLS_IGNORE	:= $(addprefix $(CONFIG_DIR)/,splat.us.weapon.yaml assets.hd.yaml assets.us.yaml)
FORMAT_SYMBOLS_FILES	:= $(filter-out $(FORMAT_SYMBOLS_IGNORE),$(wildcard $(CONFIG_DIR)/*.yaml))

# Active overlays
STAGES		:= $(patsubst $(CONFIG_DIR)/splat.$(VERSION).st%.yaml,%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).st*.yaml))
BOSSES   	:= $(patsubst $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml,%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).bo*.yaml))
SERVANTS	:= $(patsubst $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml,tt_%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).tt_*.yaml))
GAME		:= $(filter-out $(call get_targets,prefixed),$(patsubst $(CONFIG_DIR)/splat.$(VERSION).%.yaml,%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).*.yaml)))

# Toolchain
CROSS           := mipsel-linux-gnu-
LD              := $(CROSS)ld
OBJCOPY         := $(CROSS)objcopy
ALLEGREX 		:= $(BIN_DIR)/allegrex-as
WIBO            := $(BIN_DIR)/wibo
MWCCPSP         := $(BIN_DIR)/mwccpsp.exe
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
CYGNUS			:= $(BIN_DIR)/cygnus-2.7-96Q3-bin

# Symbols
BASE_SYMBOLS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

# Other tooling
BLACK			:= $(and $(PYTHON_BIN),$(PYTHON_BIN)/)black
SPLAT           := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)splat split
SOTNSTR_APP     := $(TOOLS_DIR)/sotn_str/target/release/sotn_str
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py
SHASUM          := shasum
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
CLANG			:= $(BIN_DIR)/clang-format
GOPATH          := $(HOME)/go
GO              := $(GOPATH)/bin/go
SOTNLINT		:= cargo run --release --manifest-path $(TOOLS_DIR)/lints/sotn-lint/Cargo.toml $(SRC_DIR)/
DUPS			:= cd $(TOOLS_DIR)/dups; cargo run --release -- --threshold .90 --output-file ../gh-duplicates/duplicates.txt
ASMDIFFER		:= $(TOOLS_DIR)/asm-differ/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2C_APP         := $(TOOLS_DIR)/m2c/m2c.py
PERMUTER_APP	:= $(TOOLS_DIR)/decomp-permuter
MASPSX_APP      := $(TOOLS_DIR)/maspsx/maspsx.py
MWCCGAP_APP     := $(TOOLS_DIR)/mwccgap/mwccgap.py
DOSEMU_APP		:= $(or $(shell which dosemu),/usr/bin/dosemu)
SATURN_SPLITTER_DIR := $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
SOTNDISK_DIR	:= $(TOOLS_DIR)/sotn-disk/
SOTNDISK        := $(GOPATH)/bin/sotn-disk
SOTNASSETS_DIR  := $(TOOLS_DIR)/sotn-assets/
SOTNASSETS      := $(GOPATH)/bin/sotn-assets

# Build functions
list_files		 = $(addprefix $(BUILD_DIR)/,$(shell $(PYTHON) $(TOOLS_DIR)/sotn_build/get_file_list.py list $(1) o_files -c splat))
define link
	$(muffle)$(call echo,Linking $(1),optional)
	$(muffle)$(LD) $(LD_FLAGS) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(1).ld \
		$(call if_version,pspeu,-T $(CONFIG_DIR)/symexport.$(VERSION).$(1).txt) \
		$(if $(wildcard $(CONFIG_DIR)/$(UNDEFINED_SYMS)),-T $(CONFIG_DIR)/$(UNDEFINED_SYMS)) \
		$(if $(wildcard $(CONFIG_DIR)/$(AUTO_UNDEFINED:TYPE%=undefined_syms%)),-T $(CONFIG_DIR)/$(AUTO_UNDEFINED:TYPE%=undefined_syms%)) \
		$(if $(wildcard $(CONFIG_DIR)/$(AUTO_UNDEFINED:TYPE%=undefined_funcs%)),-T $(CONFIG_DIR)/$(AUTO_UNDEFINED:TYPE%=undefined_funcs%)) \
		$(3)
endef
get_build_dirs = $(subst //,/,$(addsuffix /,$(addprefix $(BUILD_DIR)/,$(1))))
get_ovl_from_path = $(word $(or $(2),1),$(filter $(call get_targets),$(subst /, ,$(1))))
add_ovl_prefix = $(if $(filter $(call to_lower,$(1)),$(STAGES)),$(or $(2),st),$(if $(filter $(call to_lower,$(1)),$(BOSSES)),$(or $(3),bo)))$(call to_lower,$(1))
### End new header ###
### Start old header, to be removed when all targets have been transitioned ###
# Directories
DISK_DIR        := $(BUILD_DIR)/${VERSION}/disk

# Symbols
MAIN_TARGET     := $(BUILD_DIR)/main

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
MASPSX          := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.34
MASPSX_21       := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.21

DEPENDENCIES	= $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(MASPSX_APP) $(GO) python-dependencies

SOTNDISK_SOURCES   := $(shell find tools/sotn-disk -name '*.go')
SOTNASSETS_SOURCES := $(shell find tools/sotn-assets -name '*.go')
### End old header ###

ifneq (,$(filter $(VERSION),us hd)) # Both us and hd versions use the PSX platform
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

.PHONY: format
format: ##@ Format source code, clean symbols, other linting
format: format-src format-tools format-symbols format-license

.PHONY: format-src
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

.PHONY: format-tools
format-tools:
	$(BLACK) tools/*.py
	$(BLACK) tools/splat_ext/*.py
	$(BLACK) tools/split_jpt_yaml/*.py
	$(BLACK) tools/sotn_permuter/permuter_loader.py
	$(BLACK) diff_settings.py
	$(BLACK) tools/sotn_build/*.py
format-symbols:
	VERSION=us $(PYTHON) ./tools/symbols.py sort
	VERSION=hd $(PYTHON) ./tools/symbols.py sort
	VERSION=pspeu $(PYTHON) ./tools/symbols.py sort
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.dra.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.hd.dra.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.ric.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.hd.ric.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stcen.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.hd.stcen.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stchi.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stdre.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stlib.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stno0.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stno1.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stno3.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stno4.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stnp3.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stnz0.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stsel.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stst0.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stwrp.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.hd.stwrp.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.strwrp.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.bomar.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.bobo4.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.borbo3.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.borbo5.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.tt_000.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.hd.tt_000.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.tt_001.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.tt_002.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.tt_003.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.tt_004.yaml
	$(PYTHON) ./tools/symbols.py remove-orphans config/splat.us.stmad.yaml
format-license:
	find src/ | grep -E '\.c$$|\.h$$' | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | $(PYTHON) ./tools/lint-license.py - AGPL-3.0-or-later
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

.PHONY: patch
patch:
	$(DIRT_PATCHER) config/dirt.$(VERSION).json

.PHONY: check
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

.PHONY: expected
expected: check
	mkdir -p expected/build
	rm -rf expected/build/$(VERSION)
	cp -r build/$(VERSION) expected/build/

# Force to extract all the assembly code regardless if a function is already decompiled
force_extract:
	mv src src_tmp
	find $(BUILD_DIR) -type f -name "*.ld" -delete
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
	# note the lack of `version` for mad
	$(PYTHON) ./tools/symbols.py elf build/us/stmad.elf > config/symbols.stmad.txt
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
	$(PYTHON) ./tools/symbols.py elf build/us/borbo5.elf > config/symbols.us.borbo5.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_000.elf > config/symbols.us.tt_000.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_001.elf > config/symbols.us.tt_001.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_002.elf > config/symbols.us.tt_002.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_003.elf > config/symbols.us.tt_003.txt
	$(PYTHON) ./tools/symbols.py elf build/us/tt_004.elf > config/symbols.us.tt_004.txt

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

.PHONY: python-dependencies
python-dependencies: $(VENV_DIR)
	$(PIP) install -r $(TOOLS_DIR)/requirements-python.txt

$(VENV_DIR):
	$(SYSTEM_PYTHON) -m venv $(VENV_DIR)

.PHONY: update-dependencies
update-dependencies: ##@ update tools and internal dependencies
update-dependencies: $(DEPENDENCIES)
	rm $(SOTNDISK) && make $(SOTNDISK) || true
	rm $(SOTNASSETS) && make $(SOTNASSETS) || true
	cargo build --release --manifest-path ./tools/sotn_str/Cargo.toml
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
	$(PYTHON) ./tools/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.json.o: $(ASSETS_DIR)/dra/%.json
	$(PYTHON) ./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.json.o: $(ASSETS_DIR)/ric/%.json
	$(PYTHON) ./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
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
