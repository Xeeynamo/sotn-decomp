.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all

# Sets VERSION and VENV_DIR if not defined
VERSION         ?= us
VENV_DIR       	?= .venv
# For disambiguation/escaping of characters
slash		:= /
comma		:= ,
dot			:= .

# Utility functions
rwildcard  = $(subst //,/,$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)))
to_upper   = $(shell echo $(1) | tr '[:lower:]' '[:upper:]')
to_lower   = $(shell echo $(1) | tr '[:upper:]' '[:lower:]')
if_version = $(if $(filter $1,$(VERSION)),$2,$3)
#if_overlay = $(if $(filter-out $(1),$(2)),$(3))
echo = echo -e "$(subst //,/,$(1))" # Sugar function so the subst doesn't muddy echo commands

# System related variables
OS := $(subst Darwin,MacOS,$(shell uname -s))
SYSTEM_PYTHON	:= $(or $(shell which python),/usr/bin/python3) # Only used for installing venv
PYTHON_BIN		:= $(or $(realpath $(VENV_DIR)/bin/))
PYTHON          := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)python3 # This is slightly redundant to handle the slash
PIP			 	:= $(realpath $(VENV_DIR))/bin/pip3 # Pip will always use venv
BASH			:= $(or $(shell which bash),/usr/bin/bash)
BASH_FLAGS	  	:= -e -o pipefail
SHELL 			:= $(BASH) $(BASH_FLAGS)
DEPENDENCIES	:= $(VENV_DIR) $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(GO) requirements-python

# Directories
BIN_DIR         := bin
ASM_DIR         := asm/$(VERSION)
ASM_SUBDIRS 	:= $(slash) /data $(call if_version,us hd,/psxsdk /handwritten)
SRC_DIR         := src
SRC_SUBDIRS 	:= $(slash) $(call if_version,us hd,/psxsdk)
INCLUDE_DIR     := include
ASSETS_DIR      := assets
CONFIG_DIR      := config
TOOLS_DIR       := tools
PY_TOOLS_SUBDIRS:= $(addprefix $(TOOLS_DIR)/,$(slash) splat_ext/ split_jpt_yaml/ sotn_str/ sotn_permuter/sotn_permuter)
RETAIL_DISK_DIR := disks
EXTRACTED_DISK_DIR := $(RETAIL_DISK_DIR)/$(VERSION)
BUILD_DISK_DIR  := $(BUILD_DIR)/disk
BUILD_DIR       := build/$(VERSION)
EXPECTED_DIR	:= expected/$(BUILD_DIR)

# Files
CHECK_FILES := $(shell cut -d' ' -f3 $(CONFIG_DIR)/check.$(VERSION).sha)
ST_ASSETS := D_801*.bin *.gfxbin *.palbin cutscene_*.bin
CLEAN_FILES := $(ASSETS_DIR) $(ASM_DIR) $(BUILD_DIR) $(SRC_DIR)/weapon $(CONFIG_DIR)/*$(VERSION)* function_calls sotn_calltree.txt

# Toolchain related variables
# Compilers
CROSS           := mipsel-linux-gnu-
LD              := $(CROSS)ld
OBJCOPY         := $(CROSS)objcopy
# Linkers
# Assemblers
# Symbols
BASE_SYMBOLS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

# Other tooling
BLACK			:= $(and $(PYTHON_BIN),$(PYTHON_BIN)/)black
SPLAT           := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)splat split
SOTNSTR         := $(PYTHON) $(TOOLS_DIR)/sotn_str/sotn_str.py process
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py
SHASUM          := shasum
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
CLANG			:= $(BIN_DIR)/clang-format
GOPATH          := $(HOME)/go
GO              := $(GOPATH)/bin/go

ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
ASMDIFFER_APP   := diff.py
ASMDIFFER		:= $(ASMDIFFER_DIR)/$(ASM_DIFFER_APP)

M2CTX_DIR		:= $(TOOLS_DIR)
M2CTX_APP       := m2ctx.py
M2CTX           := $(PYTHON) $(M2CTX_DIR)/$(M2CTX_APP)

M2C_DIR         := $(TOOLS_DIR)/m2c
M2C_APP         := m2c.py
M2C             := $(PYTHON) $(M2C_DIR)/$(M2C_APP) -P 4

MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py
MASPSX          := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.34
MASPSX_21       := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.21

MWCCGAP_DIR     := $(TOOLS_DIR)/mwccgap
MWCCGAP_APP     := $(MWCCGAP_DIR)/mwccgap.py
MWCCGAP         := $(PYTHON) $(MWCCGAP_APP)

SOTNDISK_DIR	:= $(TOOLS_DIR)/sotn-disk
SOTNDISK_APP	:= bin/sotn-disk
SOTNDISK        := $(GOPATH)/$(SOTNDISK_APP)

SOTNASSETS_DIR	:= $(TOOLS_DIR)/sotn-assets
SOTNASSETS_APP  := bin/sotn-assets
SOTNASSETS      := $(GOPATH)/$(SOTNASSETS_APP)

# File exclusions
FORMAT_SRC_IGNORE := src/pc/3rd/cJSON/cJSON.c src/pc/3rd/cJSON/cJSON.h
REMOVE_ORPHANS_IGNORE 	:= splat.us.weapon assets.hd assets.us

# Build functions
# sel doesn't follow the same pattern as other stages, so we ignore $(2) for it in list_o_files/list_src_files
2_IGNORE_SEL = $(if $(filter-out st/sel,$(1)),$(2))
list_o_files = $(foreach file,$(call list$(3)_src_files,$(1),$(2_IGNORE_SEL)),$(BUILD_DIR)/$(file).o)
define list_src_files
	$(foreach dir,$(addprefix $(ASM_DIR)/$(1), $(ASM_SUBDIRS)),$(wildcard $(dir)/*.s))
	$(foreach dir,$(addprefix $(SRC_DIR)/$(1), $(if $(2),/,$(SRC_SUBDIRS)/)),$(wildcard $(dir)/*.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(if $(2),$(addprefix $(dir)/,$(ST_ASSETS)),$(dir)/*)))
endef
list_shared_src_files = $(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/*.c))

# leverages MWCC ability to compile data and text as separate sections to allow
# LD using --gc-sections and remove all the symbols that are unreferenced.
# symexport.*.txt is used to enforce a specific symbol and all its dependencies
# to be used. Refer to *.map to know which sections are being discarded by LD.
# Use nm to retrieve the symbol name out of a object file such as the mwo_header.

define link
	$(LD) $(LD_FLAGS) -o $(2) \
		$(call if_version,pspeu,--gc-sections) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(subst _fix,,$1).ld \
		$(call if_version,pspeu,-T $(CONFIG_DIR)/symexport.$(VERSION).$(1).txt) \
		-T $(CONFIG_DIR)/undefined_syms.$(if $(filter stmad,$(1)),beta,$(VERSION)).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto$(if $(filter-out stmad stmad_fix,$(1)),.$(VERSION)).$(subst _fix,,$(1)).txt \
		$(if $(filter-out main,$(1)),-T $(CONFIG_DIR)/undefined_funcs_auto.$(if $(filter-out stmad stmad_fix,$(1)),$(VERSION).)$(subst _fix,,$(1)).txt)
endef

define get_merged_functions 
	$(shell $(PYTHON) -c 'import yaml;\
	import os;\
	yaml_file=open(os.path.join(os.getcwd(),"config/splat.$(VERSION).$(2)$(1).yaml"));\
	config = yaml.safe_load(yaml_file);\
	yaml_file.close();\
	print(" ".join([x[2].split("/")[1] for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c" and x[2].startswith("$(1)/")]))')
endef
get_functions = $(addprefix $(BUILD_DIR)/src/$(2)/$(1)/,$(addsuffix .c.o,$(call get_merged_functions,$(1),$(2))))
# Use $(call get_targets,prefixed) when stages and bosses need to be prefixed
get_targets = $(GAME) $(if $1,$(addprefix st,$(STAGES)),$(STAGES)) $(if $1,$(addprefix bo,$(BOSSES)),$(BOSSES)) $(SERVANTS)
is_stage = $(filter $(call to_lower,$1),$(STAGES))
is_boss = $(filter $(call to_lower,$1),$(BOSSES))
# If stage then $2$1, else if boss then $3$1, else $1
get_filename = $(if $(call is_stage,$1),$(call to_lower,$2$1),$(if $(call is_boss,$1),$(call to_lower,$3$1),$(call to_lower,$1)))

ifneq ($(filter $(VERSION),us hd),) # Both us and hd versions use the PSX platform
include Makefile.psx.mk
else ifeq ($(VERSION),pspeu)
include Makefile.psp.mk
else ifeq ($(VERSION),saturn)
include Makefile.saturn.mk
endif

.PHONY: all build%
$(DEBUG).SILENT: all build%
all: build check
#/* Start build group */
build: build_$(VERSION)
#/* End build group */

#/* Start miscellaneous group */
mad_fix: build extract $$(call list_o_files,st/mad,_st) $$(call list_o_files,st,_shared) | stmad_dirs
	$(call link,stmad_fix,$@)
	$(OBJCOPY) -O binary $(BUILD_DIR)/stmad_fix.elf $(BUILD_DIR)/MAD.BIN

.PHONY: clean $(addprefix CLEAN_,$(CLEAN_FILES))
clean: $(addprefix CLEAN_,$(CLEAN_FILES))
$(addprefix CLEAN_,$(CLEAN_FILES)): CLEAN_%:
	$(call echo,Cleaning $*)
	git clean -fdx $*

.PHONY: force-symbols $(addprefix FORCE_,$(FORCE_SYMBOLS))
force-symbols: $(addprefix FORCE_,$(FORCE_SYMBOLS))
# This is currently intentionally hard coded to us because the us files are used for functions in other versions
$(addprefix FORCE_,$(FORCE_SYMBOLS)): FORCE_%:
	$(call echo,Extracting symbols for $*);$(PYTHON) $(TOOLS_DIR)/symbols.py elf $(BUILD_DIR)/$*.elf > $(CONFIG_DIR)/symbols.us.$*.txt

test:
	$(PYTHON) $(TOOLS_DIR)/symbols_test.py
context:
ifndef SOURCE
	$(error SOURCE environment variable must be set to generate context)
endif
	VERSION=$(VERSION) $(M2CTX) $(SOURCE)
	$(call echo,ctx.c has been updated.)
permuter: #placeholder
sotn: #"make clean && make -j extract && make -j build && make expected"
decompile: #".venv/bin/python3 ./tools/decompile.py"
differ: #".venv/bin/python3 ./tools/asm-differ/diff.py -mow3 --overlay"
#/* End miscellaneous group */

#/* Start expected group */
patch:
	$(DIRT_PATCHER) $(CONFIG_DIR)/dirt.$(VERSION).json
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
expected: check
	-rm -rf $(EXPECTED_DIR); cp -r $(BUILD_DIR) $(EXPECTED_DIR:$(VERSION)=)
#/* End expected group */

#/* Start extract group */
extract: extract_$(VERSION)
force-extract:
	-rm -rf /tmp/src_tmp
	mv src /tmp/src_tmp
	find $(BUILD_DIR) -type f -name "*.ld" -delete
	$(MAKE) extract
	rm -rf src/
	mv /tmp/src_tmp src
#/* End extract group */
FORCE_SYMBOLS := $(patsubst $(BUILD_DIR)/%.elf,%,$(wildcard $(BUILD_DIR)/*.elf))

#/* Start format group */
format: format-src format-tools format-symbols format-license

.PHONY: format-src $(addprefix FORMAT_,$(FORMAT_SRC))
FORMAT_SRC := $(filter-out $(FORMAT_SRC_IGNORE),$(call rwildcard,src/ include/,*.c *.h))
format-src: $(addprefix FORMAT_,$(FORMAT_SRC))
	cargo run --release --manifest-path $(TOOLS_DIR)/lints/sotn-lint/Cargo.toml $(SRC_DIR)
$(addprefix FORMAT_,$(FORMAT_SRC)): FORMAT_%: $(CLANG)
	$(CLANG) -i $*

.PHONY: format-tools $(addprefix FORMAT_,$(PY_TOOLS_SUBDIRS))
format-tools: $(addprefix FORMAT_,$(PY_TOOLS_SUBDIRS))
$(addprefix FORMAT_,$(PY_TOOLS_SUBDIRS)): FORMAT_%:
	$(call echo,Formatting $**.py); $(BLACK) $**.py

.PHONY: format-symbols% $(addprefix REMOVE_,$(FORMAT_SYMBOLS))
FORMAT_SYMBOLS 	:= $(filter-out $(addprefix $(CONFIG_DIR)/, $(addsuffix .yaml, $(REMOVE_ORPHANS_IGNORE))), $(wildcard config/*.yaml))
format-symbols: $(addprefix format-symbols-,us hd pspeu saturn) $(addprefix REMOVE_,$(FORMAT_SYMBOLS))
format-symbols-%:
	$(call echo,Sorting $* symbols); VERSION=$* $(PYTHON) $(TOOLS_DIR)/symbols.py sort
$(addprefix REMOVE_,$(FORMAT_SYMBOLS)): REMOVE_%:
	$(call echo,Removing orphan symbols from $*); $(PYTHON) $(TOOLS_DIR)/symbols.py remove-orphans $*

.PHONY: format-license
format-license:
	$(call echo,Checking for license line in code files)
	find src/ -type f -name "*.c" -or -name "*.h" | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | $(PYTHON) $(TOOLS_DIR)/lint-license.py - AGPL-3.0-or-later
	$(foreach item,$(addprefix include/, game.h entity.h items.h lba.h memcard.h),$(PYTHON) $(TOOLS_DIR)/lint-license.py $(item) AGPL-3.0-or-later;)
#/* End format group */

#/* Start extract-disk group */
extract-disk: extract-disk-$(VERSION)
$(DEBUG).SILENT: extract-disk-us
extract-disk-us: $(SOTNDISK)
	$(SOTNDISK) extract $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)
$(addprefix extract-disk-, pspeu hd):
	mkdir -p $(EXTRACTED_DISK_DIR:$(VERSION)=pspeu)
	7z x -y $(RETAIL_DISK_DIR)/sotn.pspeu.iso -o$(EXTRACTED_DISK_DIR:$(VERSION)=pspeu)
extract-disk_saturn:
	bchunk $(RETAIL_DISK_DIR)/sotn.$(VERSION).bin $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)/sotn.$(VERSION).iso
	-7z x $(RETAIL_DISK_DIR)/sotn.$(VERSION).iso01.iso -o$(EXTRACTED_DISK_DIR)
#/* End extract-disk group */

#/* Start disk-prepare group */
.PHONY: disk%
$(DEBUG).SILENT: disk%
disk: disk-prepare
	$(SOTNDISK) make $(BUILD_DIR:/$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba
disk-prepare  = $(1)/$(1).BIN $(1)/F_$(1).BIN
DISK_PREPARE := DRA.BIN BIN/RIC.BIN ST/SEL/SEL.BIN
DISK_PREPARE += $(addprefix ST/,$(foreach target,$(filter-out sel,$(STAGES)),$(call disk-prepare,$(call to_upper,$(target)))))
DISK_PREPARE += $(addprefix BOSS/,$(foreach target,$(BOSSES),$(call disk-prepare,$(call to_upper,$(target)))))
DISK_PREPARE += $(addprefix SERVANT/,$(call to_upper,$(addsuffix .BIN,$(SERVANTS))))
disk-prepare: build $(SOTNDISK)
	mkdir -p $(BUILD_DISK_DIR)
	cp -r $(EXTRACTED_DISK_DIR)/* $(BUILD_DISK_DIR)
	cp $(BUILD_DIR)/main.exe $(BUILD_DISK_DIR)/SLUS_000.67
	$(foreach item,$(DISK_PREPARE),cp $(BUILD_DIR)/$(notdir $(item)) $(BUILD_DISK_DIR)/$(item);)
disk-debug: disk-prepare
	cd $(TOOLS_DIR)/sotn-debugmodule && make
	cp $(BUILD_DIR:$(VERSION)=)/sotn-debugmodule.bin $(BUILD_DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make $(BUILD_DIR:$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba
#/* End disk-prepare group */

#/* Start dump-disk group */
.PHONY: dump-disk% $(RETAIL_DISK_DIR)/sotn.%.bin $(RETAIL_DISK_DIR)/sotn.%.cue
dump-disk: dump-disk_$(VERSION)
$(addprefix dump-disk_, eu hk jp10 jp11 saturn us usproto): $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue
dump-disk_%:
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
#/* End dump-disk group */

#/* Start function-finder group */
# Currently broken because of force-symbols
.PHONY: function-finder duplicates-report
function-finder: graphviz duplicates-report
	-$(PYTHON) $(TOOLS_DIR)/analyze_calls.py --output_dir=$(TOOLS_DIR)/function_calls/
	git clean -fdx $(ASM_DIR)/
	git checkout $(CONFIG_DIR)/
	rm -f $(BUILD_DIR)/main.ld
	rm -f $(BUILD_DIR)/weapon.ld
	$(MAKE) extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/function_finder_$(VERSION).py --no-fetch --use-call-trees > $(TOOLS_DIR)/gh-duplicates/functions.md
	-rm -rf $(TOOLS_DIR)/gh-duplicates/function_calls/
	mv $(TOOLS_DIR)/function_calls/ $(TOOLS_DIR)/gh-duplicates/
	mv $(TOOLS_DIR)/function_graphs.md $(TOOLS_DIR)/gh-duplicates/

# Currently broken because of force-symbols
duplicates-report: force-symbols force-extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/fix_matchings.py
	mkdir -p $(TOOLS_DIR)/gh-duplicates
	cd $(TOOLS_DIR)/dups; \
	    cargo run --release -- \
            --threshold .90 \
            --output-file ../gh-duplicates/duplicates.txt
#/* End function-finder group */

#/* Start dependency group */
.PHONY: update-dependencies dpendencies% git-submodules graphviz requirements%
update-dependencies: $(DEPENDENCIES)
	git clean -fd $(BIN_DIR)/
dependencies-us: $(MASPSX_APP) 
dependencies-pspeu: $(ALLEGREX_AS) $(MWCCGAP_APP)
dependencies-hd: dependencies-us
dependencies-saturn: $(SATURN_SPLITTER_APP) $(DOSEMU)
git-submodules: $(ASMDIFFER_APP) $(M2C_APP) $(MASPSX_APP) $(MWCCGAP_APP) $(SATURN_SPLITTER_APP)
requirements-python: $(VENV_DIR)
	$(PIP) install -r $(TOOLS_DIR)/requirements-python.txt
graphviz: $(VENV_DIR)
	$(PIP) install --upgrade graphviz
#/* End dependency group */

#/* Start app install group */
$(ASMDIFFER_APP):
	git submodule update --init $(ASMDIFFER_DIR)
$(M2C_APP):
	git submodule update --init $(M2C_DIR)
	$(PIP) install --upgrade pycparser
$(VENV_DIR):
	$(SYSTEM_PYTHON) -m venv $(VENV_DIR)
$(BIN_DIR)/%: $(BIN_DIR)/%.tar.gz
	sha256sum --check $<.sha256
	cd $(BIN_DIR) && tar -xzf ../$<
	rm $<
	touch $@
$(BIN_DIR)/%.tar.gz: $(BIN_DIR)/%.tar.gz.sha256
	wget -O $@ https://github.com/Xeeynamo/sotn-decomp/releases/download/cc1-psx-26/$*.tar.gz
$(M2CTX_APP):
	curl -o $@ https://raw.githubusercontent.com/ethteck/m2ctx/main/m2ctx.py
$(GO):
	curl -L -o go1.22.4.linux-amd64.tar.gz https://go.dev/dl/go1.22.4.linux-amd64.tar.gz
	tar -C $(HOME) -xzf go1.22.4.linux-amd64.tar.gz
	rm go1.22.4.linux-amd64.tar.gz
$(SOTNDISK_APP): $(GO) $(shell find $(SOTNDISK_DIR) -type f -name '*.go')
	rm $(SOTNDISK) || true; cd $(SOTNDISK_DIR); $(GO) install
$(SOTNASSETS_APP): $(GO) $(shell find $(SOTNASSETS_DIR) -type f -name '*.go')
	rm $(SOTNASSETS) || true; cd $(SOTNASSETS_DIR); $(GO) install
$(MASPSX_APP):
	git submodule update --init $(MASPSX_DIR)
$(WIBO):
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check $(WIBO).sha256
	chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) $(BIN_DIR)/mwccpsp_219
$(MWCCGAP_APP):
	git submodule update --init $(MWCCGAP_DIR)
#/* End app install group */



# this help target will find targets which are followed by a comment beginning with '#' '#' '@' and
# print them in a summary form. Any comments on a line by themselves with start with `#' '#' '@'
# will act as section dividers.
.PHONY: help
$(DEBUG).SILENT: help
help:
	printf "\nUsage: make [VERSION=version] <target> …\n"
	grep -F -h "##@" $(MAKEFILE_LIST) | grep -F -v "grep -F" | sed -e 's/\\$$//' | awk 'BEGIN {FS = ":*[[:space:]]*##@[[:space:]]?"}; \
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
force-symbols: ##@ Extract a full list of symbols from a successful build
context: ##@ create a context for decomp.me. Set the SOURCE variable prior to calling this target
extract-disk: ##@ Extract game files from a disc image.
update-dependencies: ##@ update tools and internal dependencies

##@
##@ Disc Dumping Targets
##@

dump-disk: ##@ dump a physical game disk