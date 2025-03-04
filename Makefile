.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all

# Preflight checks
OS := $(subst Darwin,MacOS,$(shell uname -s))

ifeq ($(VERSION),)
$(info VERSION not defined, defaulting to VERSION=us)
VERSION         ?= us
endif

WHICH_PYTHON := $(shell which python3)
ifeq ($(WHICH_PYTHON),)
WHICH_PYTHON := /usr/bin/python3
$(info The python3 executable path could not be identified, defaulting to /usr/bin/python3)
endif

BASH := $(shell which bash)
ifeq ($(BASH),)
$(info The bash executable path could not be identified, defaulting to /usr/bin/bash)
BASH := /usr/bin/bash
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
CONFIG_DIR      := config
TOOLS_DIR       := tools
BUILD_DIR       := build/$(VERSION)
EXPECTED_DIR	:= expected/$(BUILD_DIR)
BUILD_DISK_DIR  := $(BUILD_DIR)/disk
RETAIL_DISK_DIR := disks
EXTRACTED_DISK_DIR := $(RETAIL_DISK_DIR)/$(VERSION)

# Symbols
BASE_SYMBOLS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

# Tooling
BASH_FLAGS	  	:= -e -o pipefail
SHELL 			 = $(BASH) $(BASH_FLAGS)
VENV_DIR       	?= .venv
ifneq ($(wildcard $(VENV_DIR)),)
PYTHON_BIN		:= $(realpath $(VENV_DIR))/bin/
endif
PYTHON          := $(PYTHON_BIN)python3
BLACK			:= $(PYTHON_BIN)black
PIP			 	:= $(realpath $(VENV_DIR))/bin/pip3
INLINE_PYTHON	:= $(PYTHON) -c
SPLAT           := $(PYTHON_BIN)splat split
ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
ASMDIFFER_APP   := $(ASMDIFFER_DIR)/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2CTX           := $(PYTHON) $(M2CTX_APP)
M2C_DIR         := $(TOOLS_DIR)/m2c
M2C_APP         := $(M2C_DIR)/m2c.py
M2C             := $(PYTHON) $(M2C_APP)
M2C_ARGS        := -P 4
SOTNSTR         := $(PYTHON) $(TOOLS_DIR)/sotn_str/sotn_str.py process
GO              := $(HOME)/go/bin/go
GOPATH          := $(HOME)/go
SOTNDISK        := $(GOPATH)/bin/sotn-disk
SOTNASSETS      := $(GOPATH)/bin/sotn-assets
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py
SHASUM          := shasum

DEPENDENCIES	:= $(VENV_DIR) $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(GO) requirements-python

SOTNDISK_SOURCES   := $(shell find $(TOOLS_DIR)/sotn-disk -name '*.go')
SOTNASSETS_SOURCES := $(shell find $(TOOLS_DIR)/sotn-assets -name '*.go')

CHECK_FILES := $(shell cut -d' ' -f3 $(CONFIG_DIR)/check.$(VERSION).sha)

ROOT		:= /
ASM_SUBDIRS := $(ROOT) /data
SRC_SUBDIRS := $(ROOT)
ifneq ($(filter $(VERSION),us hd),)
ASM_SUBDIRS += /psxsdk /handwritten
SRC_SUBDIRS += /psxsdk
endif
ST_ASSETS = D_801*.bin *.gfxbin *.palbin cutscene_*.bin

define list_src_files
	$(foreach dir,$(addprefix $(ASM_DIR)/$(1), $(ASM_SUBDIRS)),$(wildcard $(dir)/*.s))
	$(foreach dir,$(addprefix $(SRC_DIR)/$(1), $(if $(2),/,$(SRC_SUBDIRS)/)),$(wildcard $(dir)/*.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(if $(2),$(addprefix $(dir)/,$(ST_ASSETS)),$(dir)/*)))
endef
list_shared_src_files = $(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/*.c))
list_src_files_filtered = $(call list$(3)_src_files,$(1),$(if $(filter-out st/sel,$(1)),$(2)))
list_o_files = $(foreach file,$(list_src_files_filtered),$(BUILD_DIR)/$(file).o)

# leverages MWCC ability to compile data and text as separate sections to allow
# LD using --gc-sections and remove all the symbols that are unreferenced.
# symexport.*.txt is used to enforce a specific symbol and all its dependencies
# to be used. Refer to *.map to know which sections are being discarded by LD.
# Use nm to retrieve the symbol name out of a object file such as the mwo_header.
define link
	$(LD) $(LD_FLAGS) -o $(2) \
		$(call if_version,pspeu,--gc-sections) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(1).ld \
		$(call if_version,pspeu,-T $(CONFIG_DIR)/symexport.$(VERSION).$(1).txt) \
		-T $(CONFIG_DIR)/undefined_syms.$(if $(filter stmad,$(1)),beta,$(VERSION)).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(if $(filter-out stmad,$(1)),$(VERSION).)$(1).txt \
		$(if $(filter-out main,$(1)),-T $(CONFIG_DIR)/undefined_funcs_auto.$(if $(filter-out stmad,$(1)),$(VERSION).)$(1).txt)
endef

# Use $(call get_targets) when the non-prefised name is needed
# Use $(call get_targets,st,bo) when stages and bosses need to be prefixed
get_targets = $(GAME) $(addprefix $1,$(STAGES)) $(addprefix $2,$(BOSSES)) $(SERVANTS)

to_upper = $(shell echo $(1) | tr '[:lower:]' '[:upper:]')
to_lower = $(shell echo $(1) | tr '[:upper:]' '[:lower:]')
echo = echo -e "$(1)"
get_filename = $(if $(filter $(call to_lower,$1),$(STAGES)),$(call to_lower,$2$1),$(if $(filter $(call to_lower,$1),$(BOSSES)),$(call to_lower,$3$1),$(call to_lower,$1)))
if_version = $(if $(filter $1,$(VERSION)),$2,$3)

ifneq ($(filter $(VERSION),us hd),) # Both us and hd versions use the PSX platform
include Makefile.psx.mk
else ifeq ($(VERSION),pspeu)
include Makefile.psp.mk
else ifeq ($(VERSION),saturn)
include Makefile.saturn.mk
endif

# this help target will find targets which are followed by a comment beginning with '#' '#' '@' and
# print them in a summary form. Any comments on a line by themselves with start with `#' '#' '@'
# will act as section dividers.
.PHONY: help
help:
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

##@ Variables
##@
##@     VERSION              the game version to build (us, hd, pspeu, saturn, pc) (Default: us)
##@
##@ Primary Targets
##@

all: ##@ (Default) build and check
extract: ##@ split game files into assets and assembly
build: ##@ build game files
clean: ##@ clean extracted files, assets, and build artifacts

##@
##@ Misc Targets
##@

help: ##@ Print listing of key targets with their descriptions
format: ##@ Format source code, clean symbols, other linting
check: ##@ compare built files to original game files
force_symbols: ##@ Extract a full list of symbols from a successful build
context: ##@ create a context for decomp.me. Set the SOURCE variable prior to calling this target
extract_disk: ##@ Extract game files from a disc image.
update-dependencies: ##@ update tools and internal dependencies

##@
##@ Disc Dumping Targets
##@

dump_disk: ##@ dump a physical game disk


# Pseudo targets
.PHONY: all
all: build check

.PHONY: extract 
extract: extract_$(VERSION)

.PHONY: build 
build: build_$(VERSION)

.PHONY: clean
CLEAN_TARGETS := $(ASSETS_DIR) $(ASM_DIR) $(BUILD_DIR) $(SRC_DIR)/weapon $(CONFIG_DIR)/*$(VERSION)* function_calls sotn_calltree.txt
clean: $(addprefix clean_, $(subst /,_,$(CLEAN_TARGETS)))
clean_%:
	git clean -fdx $(subst _,/,$*)

.PHONY: format
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
$(DEBUG).SILENT: format-tools
FORMAT_TOOLS := $(addprefix $(TOOLS_DIR)/, $(ROOT) splat_ext/ split_jpt_yaml/ sotn_str/ sotn_permuter/sotn_permuter )
format-tools:
	$(foreach item, $(FORMAT_TOOLS://=/),$(call echo,Formatting $(item)*.py); $(BLACK) $(item)*.py;)

.PHONY: format-symbols
$(DEBUG).SILENT: format-symbols
ORPHAN_EXCLUDE 	:= splat.us.weapon assets.hd assets.us
REMOVE-ORPHANS 	:= $(filter-out $(addprefix $(CONFIG_DIR)/, $(addsuffix .yaml, $(ORPHAN_EXCLUDE))), $(wildcard config/*.yaml))
format-symbols:
	$(foreach item, us hd pspeu saturn, $(call echo,Sorting $(item) symbols); VERSION=$(item) $(PYTHON) $(TOOLS_DIR)/symbols.py sort;)
	$(foreach item, $(REMOVE-ORPHANS), $(call echo,Removing orphan symbols from $(item)); $(PYTHON) $(TOOLS_DIR)/symbols.py remove-orphans $(item);)

.PHONY: format-license
$(DEBUG).SILENT: format-license
format-license:
	$(call echo,Checking for license line in code files)
	find src/ -type f -name "*.c" -or -name "*.h" | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | $(PYTHON) $(TOOLS_DIR)/lint-license.py - AGPL-3.0-or-later
	$(foreach item,$(addprefix include/, game.h entity.h items.h lba.h memcard.h),$(PYTHON) $(TOOLS_DIR)/lint-license.py $(item) AGPL-3.0-or-later;)
# fast-format
.PHONY: patch
patch:
	$(DIRT_PATCHER) $(CONFIG_DIR)/dirt.$(VERSION).json

.PHONY: check
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

.PHONY: expected
expected: check
	mkdir -p expected/build
	rm -rf expected/build/$(VERSION)
	cp -r build/$(VERSION) expected/build/

force_extract:
	mv src src_tmp
	find $(BUILD_DIR) -type f -name "*.ld" -delete
	make extract -j
	rm -rf src/
	mv src_tmp src

# This is currently intentionally hard coded to us because the us files are used for functions in other versions
.PHONY: force_symbols
$(DEBUG).SILENT: force_symbols
FORCE_SYMBOLS := $(patsubst $(BUILD_DIR)/%.elf,%,$(wildcard $(BUILD_DIR)/*.elf))
force_symbols:
	$(foreach item,$(FORCE_SYMBOLS),$(call echo,$(Extracting symbols for $(item)));$(PYTHON) $(TOOLS_DIR)/symbols.py elf $(BUILD_DIR)/$(item).elf > $(CONFIG_DIR)/symbols.us.$(item).txt;)

context:
	$(VERSION) $(M2CTX) $(SOURCE)
	$(call echo,ctx.c has been updated.)

# Grouping all extract_disk together for consistency since hd and pspeu use the extract_disk target
.PHONY: extract_disk%
$(DEBUG).SILENT: extract_disk_us
extract_disk: extract_disk_$(VERSION)
extract_disk_us: $(SOTNDISK)
	$(SOTNDISK) extract $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)
$(addprefix extract_disk_, pspeu hd):
	mkdir -p $(EXTRACTED_DISK_DIR:$(VERSION)=pspeu)
	7z x -y $(RETAIL_DISK_DIR)/sotn.pspeu.iso -o$(EXTRACTED_DISK_DIR:$(VERSION)=pspeu)
extract_disk_saturn:
	bchunk $(RETAIL_DISK_DIR)/sotn.$(VERSION).bin $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)/sotn.$(VERSION).iso
	-7z x $(RETAIL_DISK_DIR)/sotn.$(VERSION).iso01.iso -o$(EXTRACTED_DISK_DIR)

.PHONY: disk_prepare
$(DEBUG).SILENT: disk_prepare
disk_prepare  = $(1)/$(1).BIN $(1)/F_$(1).BIN
DISK_PREPARE := DRA.BIN BIN/RIC.BIN ST/SEL/SEL.BIN
DISK_PREPARE += $(addprefix ST/,$(foreach target,$(filter-out sel,$(STAGES)),$(call disk_prepare,$(call to_upper,$(target)))))
DISK_PREPARE += $(addprefix BOSS/,$(foreach target,$(BOSSES),$(call disk_prepare,$(call to_upper,$(target)))))
DISK_PREPARE += $(addprefix SERVANT/,$(call to_upper,$(addsuffix .BIN,$(SERVANTS))))
disk_prepare: build $(SOTNDISK)
	mkdir -p $(BUILD_DISK_DIR)
	cp -r $(EXTRACTED_DISK_DIR)/* $(BUILD_DISK_DIR)
	cp $(BUILD_DIR)/main.exe $(BUILD_DISK_DIR)/SLUS_000.67
	$(foreach item,$(DISK_PREPARE),cp $(BUILD_DIR)/$(notdir $(item)) $(BUILD_DISK_DIR)/$(item);)

disk: disk_prepare
	$(SOTNDISK) make $(BUILD_DIR:/$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba
disk_debug: disk_prepare
	cd $(TOOLS_DIR)/sotn-debugmodule && make
	cp $(BUILD_DIR:$(VERSION)=)/sotn-debugmodule.bin $(BUILD_DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make $(BUILD_DIR:$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba

test:
	$(PYTHON) $(TOOLS_DIR)/symbols_test.py

# Needs validation
function-finder: graphviz duplicates-report
	-$(PYTHON) $(TOOLS_DIR)/analyze_calls.py --output_dir=$(TOOLS_DIR)/function_calls/
	git clean -fdx $(ASM_DIR)/
	git checkout $(CONFIG_DIR)/
	rm -f $(BUILD_DIR)/main.ld
	rm -rf $(BUILD_DIR)/weapon.ld
	$(MAKE) -j extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/function_finder_$(VERSION).py --no-fetch --use-call-trees > $(TOOLS_DIR)/gh-duplicates/functions.md
	-rm -rf $(TOOLS_DIR)/gh-duplicates/function_calls/
	mv $(TOOLS_DIR)/function_calls/ $(TOOLS_DIR)/gh-duplicates/
	mv $(TOOLS_DIR)/function_graphs.md $(TOOLS_DIR)/gh-duplicates/

graphviz:
	$(PIP) install --upgrade graphviz

# Needs validation
duplicates-report: force_symbols force_extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/fix_matchings.py
	mkdir -p $(TOOLS_DIR)/gh-duplicates
	cd $(TOOLS_DIR)/dups; \
	    cargo run --release -- \
            --threshold .90 \
            --output-file ../gh-duplicates/duplicates.txt
			
.PHONY: requirements-python
requirements-python: $(VENV_DIR)
	$(PIP) install -r $(TOOLS_DIR)/requirements-python.txt

$(VENV_DIR):
	$(WHICH_PYTHON) -m venv $(VENV_DIR)

.PHONY: update-dependencies
update-dependencies: $(DEPENDENCIES)
	-rm $(SOTNDISK) && make $(SOTNDISK)
	-rm $(SOTNASSETS) && make $(SOTNASSETS)
	git clean -fd $(BIN_DIR)/

$(BIN_DIR)/%: $(BIN_DIR)/%.tar.gz
	sha256sum --check $<.sha256
	cd $(BIN_DIR) && tar -xzf ../$<
	rm $<
	touch $@
$(BIN_DIR)/%.tar.gz: $(BIN_DIR)/%.tar.gz.sha256
	wget -O $@ https://github.com/Xeeynamo/sotn-decomp/releases/download/cc1-psx-26/$*.tar.gz
$(M2CTX_APP):
	curl -o $@ https://raw.githubusercontent.com/ethteck/m2ctx/main/m2ctx.py

$(ASMDIFFER_APP):
	git submodule update --init $(ASMDIFFER_DIR)
$(M2C_APP):
	git submodule update --init $(M2C_DIR)
	$(PIP) install --upgrade pycparser
$(GO):
	curl -L -o go1.22.4.linux-amd64.tar.gz https://go.dev/dl/go1.22.4.linux-amd64.tar.gz
	tar -C $(HOME) -xzf go1.22.4.linux-amd64.tar.gz
	rm go1.22.4.linux-amd64.tar.gz
$(SOTNDISK): $(GO) $(SOTNDISK_SOURCES)
	cd $(TOOLS_DIR)/sotn-disk; $(GO) install
$(SOTNASSETS): $(GO) $(SOTNASSETS_SOURCES)
	cd $(TOOLS_DIR)/sotn-assets; $(GO) install

.PHONY: dump_disk
dump_disk: dump_disk_$(VERSION)
$(addprefix dump_disk_, eu hk jp10 jp11 saturn us usproto): $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue

dump_disk_%:
	$(error Automated dumping of $* is not supported)

$(RETAIL_DISK_DIR)/sotn.%.bin $(RETAIL_DISK_DIR)/sotn.%.cue:
	@( which -s cdrdao && which -s toc2cue ) || (echo "cdrdao(1) and toc2cue(1) must be installed" && exit 1 )
	cd $(RETAIL_DISK_DIR) && \
        DEVICE="$(shell cdrdao scanbus 2>&1 | grep -vi cdrdao | head -n1 | sed 's/ : [^:]*$$//g')" && \
        cdrdao read-cd \
            --read-raw \
            --datafile sotn.$*.bin \
            --device "$$DEVICE" \
            --driver generic-mmc-raw \
            sotn.$*.toc && \
        toc2cue sotn.$*.toc sotn.$*.cue && \
        rm sotn.$*.toc
