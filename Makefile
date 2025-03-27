.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all
PHONY_TARGETS := # Empty variable
MUFFLED_TARGETS := # Empty variable

VERSION		?= us# Only when env not set
VENV_DIR	?= .venv# Can be overriden with env
comma		:= ,# For escaping a literal comma
muffle 		:= $(if $(DEBUG),,@)# Allows DEBUG to unmuffle targets which can't use .SILENT

# Utility functions
rwildcard	= $(subst //,/,$(foreach dir,$(wildcard $(1:=/*)),$(call rwildcard,$(dir),$(2)) $(filter $(subst *,%,$(2)),$(dir))))
echo		= $(muffle)$(if $(and $(QUIET),$(2)),,echo -e "$(subst //,/,$(1))";)# Allows for optional terminal messages
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

# Active overlays
STAGES		:= $(patsubst $(CONFIG_DIR)/splat.$(VERSION).st%.yaml,%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).st*.yaml))
BOSSES   	:= $(patsubst $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml,%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).bo*.yaml))
SERVANTS	:= $(patsubst $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml,tt_%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).tt_*.yaml))
GAME		:= $(filter-out $(call get_targets,prefixed),$(patsubst $(CONFIG_DIR)/splat.$(VERSION).%.yaml,%,$(wildcard $(CONFIG_DIR)/splat.$(VERSION).*.yaml)))

# Toolchain
CROSS			:= $(call if_version,saturn,sh-elf-,mipsel-linux-gnu-)
LD              := $(CROSS)ld
OBJCOPY         := $(CROSS)objcopy
OBJDUMP			:= $(CROSS)objdump
ALLEGREX 		:= $(BIN_DIR)/allegrex-as
WIBO            := $(BIN_DIR)/wibo
MWCCPSP         := $(BIN_DIR)/mwccpsp.exe
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
CYGNUS			:= $(BIN_DIR)/cygnus-2.7-96Q3-bin
CC1_SATURN		:= $(BUILD_DIR)/CC1.EXE

# Symbols
BASE_SYMBOLS	 = symbols.$(if $(filter mad,$(1)),beta,$(VERSION)).txt
UNDEFINED_SYMS 	 = undefined_syms.$(if $(filter stmad,$(1)),beta,$(VERSION)).txt
AUTO_UNDEFINED	 = TYPE_auto$(if $(filter-out stmad,$(1)),.$(VERSION)).$(1).txt

# Other tooling
BLACK			:= $(and $(PYTHON_BIN),$(PYTHON_BIN)/)black
SPLAT           := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)splat split
SOTNSTR         := ./tools/sotn_str/target/release/sotn_str process
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) $(TOOLS_DIR)/dirt_patcher.py
SHASUM          := shasum
GFXSTAGE        := $(PYTHON) $(TOOLS_DIR)/gfxstage.py
PNG2S           := $(PYTHON) $(TOOLS_DIR)/png2s.py
CLANG			:= $(BIN_DIR)/clang-format
GO              := $(HOME)/go/bin/go
SOTNLINT		:= cargo run --release --manifest-path $(TOOLS_DIR)/lints/sotn-lint/Cargo.toml $(SRC_DIR)/
DUPS			:= cd $(TOOLS_DIR)/dups; cargo run --release -- --threshold .90 --output-file ../gh-duplicates/duplicates.txt
SOTNSTR_APP     := $(TOOLS_DIR)/sotn_str/target/release/sotn_str
ASMDIFFER_APP	:= $(TOOLS_DIR)/asm-differ/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2C_APP         := $(TOOLS_DIR)/m2c/m2c.py
PERMUTER_APP	:= $(TOOLS_DIR)/decomp-permuter
MASPSX_APP      := $(TOOLS_DIR)/maspsx/maspsx.py
MWCCGAP_APP     := $(TOOLS_DIR)/mwccgap/mwccgap.py
DOSEMU_DIR		:= $(TOOLS_DIR)/dosemu-deb
DOSEMU_APP		:= $(or $(shell which dosemu),/usr/bin/dosemu)
SATURN_SPLITTER_DIR := $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract
SOTNDISK_DIR	:= $(TOOLS_DIR)/sotn-disk/
SOTNDISK        := $(SOTNDISK_DIR)/sotn-disk
SOTNASSETS_DIR  := $(TOOLS_DIR)/sotn-assets/
SOTNASSETS      := $(SOTNASSETS_DIR)/sotn-assets

# Build functions
define get_src_files
	$(foreach dir,$(ASM_DIR)/$(1)/ $(addprefix $(ASM_DIR)/$(1)/,$(ASM_SUBDIRS)),$(wildcard $(dir)/*.s))
	$(foreach dir,$(SRC_DIR)/$(1)/ $(addprefix $(SRC_DIR)/$(1)/,$(if $(2),,$(SRC_SUBDIRS))),$(wildcard $(dir)/*.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(if $(2),$(addprefix $(dir)/,$(ST_ASSETS)),$(dir)/*)))
endef
get_shared_src_files = $(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/*.c))
# sel doesn't follow the same pattern as other stages, so we ignore $(2) for it in get_o_files/get_src_files
2_IGNORE_SEL = $(if $(filter-out st/sel,$(1)),$(2))
get_o_files = $(subst //,/,$(foreach file,$(call get$(3)_src_files,$(1),$(2_IGNORE_SEL)),$(BUILD_DIR)/$(file).o))
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
define get_conf_merged
	$(shell $(PYTHON) -c 'import yaml;\
	import os;\
	yaml_file=open("$(CONFIG_DIR)/splat.$(VERSION).$(2)$(1).yaml");\
	config = yaml.safe_load(yaml_file); yaml_file.close();\
	c_subsegments = [x for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c"];\
	merged_functions = [x[2].split("/")[1] for x in c_subsegments if str(x[2]).startswith("$(1)/")];\
	print(" ".join(merged_functions))')
endef
get_auto_merge = $(addsuffix .o,$(wildcard $(subst _psp,,$(filter-out $(wildcard src/$(2)/$(1)_psp/*.c),src/$(2)/$(1)_psp/$(AUTO_MERGE_FILES)))))
get_merged_o_files = $(addprefix $(BUILD_DIR)/src/$(2)/$(1)/,$(addsuffix .c.o,$(call get_conf_merged,$(1),$(2)))) $(addprefix $(BUILD_DIR)/,$(call get_auto_merge,$(1),$(2)))
get_psp_o_files = $(call get_merged_o_files,$(1),$(2)) $(call get_o_files,$(2)/$(1)_psp) $(if $(filter-out dra,$(1)),$(subst //,/,$(BUILD_DIR)/assets/$(2)/$(1)/mwo_header.bin.o))
get_build_dirs = $(subst //,/,$(addsuffix /,$(addprefix $(BUILD_DIR)/,$(1))))
get_ovl_from_path = $(word $(or $(2),1),$(filter $(call get_targets),$(subst /, ,$(1))))
add_ovl_prefix = $(if $(filter $(call to_lower,$(1)),$(STAGES)),$(or $(2),st),$(if $(filter $(call to_lower,$(1)),$(BOSSES)),$(or $(3),bo)))$(call to_lower,$(1))

all: build check
extract: extract_$(VERSION)
build: build_$(VERSION)

$(addprefix CLEAN_,$(CLEAN_FILES)): CLEAN_%:
	$(call echo,Cleaning $*) git clean -fdxq $*
clean: $(addprefix CLEAN_,$(CLEAN_FILES))

# Targets for performing various automated formatting tasks
format-src.run:
	rm $@ > /dev/null 2>&1 || true
	$(call echo,Running clang to format src/* and include/* (this may take some time))
$(addprefix FORMAT_,$(FORMAT_SRC_FILES)): FORMAT_%: $(CLANG) format-src.run
	echo "$*" >> format-src.run
	$(CLANG) -i $*
format-src: $(addprefix FORMAT_,$(FORMAT_SRC_FILES))
# Redirecting sotn-lint stdout because even if there was sometshing useful, you'd never see it because of the output spam
	$(SOTNLINT) 1>/dev/null; rm $@.run

$(addprefix FORMAT_,$(PY_TOOLS_DIRS)): FORMAT_%: | $(VENV_DIR)
	$(call echo,Formatting $**.py) $(BLACK) $**.py
format-tools: $(addprefix FORMAT_,$(PY_TOOLS_DIRS))

format-symbols.run:
	rm $@ > /dev/null 2>&1 || true
	$(call echo,Removing orphan symbols using splat configs)
$(addprefix FORMAT_,$(FORMAT_SYMBOLS_FILES)): FORMAT_%: format-symbols.run | $(VENV_DIR)
	echo "$*" >> format-symbols.run
	$(PYTHON) $(TOOLS_DIR)/symbols.py remove-orphans $*
$(addprefix format-symbols_,us pspeu hd saturn): format-symbols_%: | $(VENV_DIR)
	$(call echo,Sorting $* symbols) VERSION=$* $(PYTHON) $(TOOLS_DIR)/symbols.py sort
format-symbols: $(addprefix format-symbols_,us pspeu hd saturn) $(addprefix FORMAT_,$(FORMAT_SYMBOLS_FILES))
	rm $@.run > /dev/null 2>&1 || true

format-license:
	$(call echo,Checking for license line in code files)
	find src/ -type f -name "*.c" -or -name "*.h" | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | $(PYTHON) $(TOOLS_DIR)/lint-license.py - AGPL-3.0-or-later
	$(foreach item,$(addprefix include/,game.h entity.h items.h lba.h memcard.h),$(PYTHON) $(TOOLS_DIR)/lint-license.py $(item) AGPL-3.0-or-later;)

format: format-src format-tools format-symbols format-license

# Step 1/3 of expected
patch: $(CONFIG_DIR)/dirt.$(VERSION).json build
	$(DIRT_PATCHER) $(CONFIG_DIR)/dirt.$(VERSION).json

# Step 2/3 of expected
check: $(CONFIG_DIR)/check.$(VERSION).sha $(CHECK_FILES) patch
	$(SHASUM) --check $< | awk 'BEGIN{ FS=": " }; { \
        printf "%s\t[ ", $$1; \
        if ($$2 == "OK") \
            color = 28;   \
        else \
            color = 196;   \
        system("tput setaf " color "; printf " $$2 "; tput sgr0"); \
        printf " ]\n"; \
    }' | column --separator $$'\t' --table

# Step 3/3 of expected
# This looks a little silly, but it handles making sure that the expected/ directory exists, then clears the old data out.
# The cp will fail if expected/ doesn't exist and it is only used here so a prerequisite doesn't really make sense.
expected: check
	$(call echo,Copying build files to expected/)
	mkdir -p expected/$(BUILD_DIR); rm -rf expected/$(BUILD_DIR)
	cp -r $(BUILD_DIR) expected/$(BUILD_DIR)

force-extract:
	@rm -rf /tmp/src_tmp || true; mv src /tmp/src_tmp
	find $(BUILD_DIR) -type f -name "*.ld" -delete || true
	$(MAKE) extract
	rm -rf src/; mv /tmp/src_tmp src

# Other utility targets
force_symbols_ovls = $(patsubst $(BUILD_DIR)/%.elf,%,$(wildcard $(BUILD_DIR:$(VERSION)=us)/*.elf))
# This is currently intentionally hard coded to us because the us symbols files are used for finding functions in other versions
$(addprefix FORCE_,$(force_symbols_ovls)): FORCE_%: | $(VENV_DIR)
	$(call echo,Extracting symbols for $*) $(PYTHON) $(TOOLS_DIR)/symbols.py elf $(BUILD_DIR)/$*.elf > $(CONFIG_DIR)/symbols.us.$*.txt
force-symbols: $(addprefix FORCE_,$(force_symbols_ovls))

context: $(M2CTX_APP) | $(VENV_DIR)
ifndef SOURCE
	$(error SOURCE environment variable must be set to generate context)
endif
	VERSION=$(VERSION) $(PYTHON) $(M2CTX_APP) $(SOURCE)
	$(call echo,ctx.c has been updated.)

# Targets to extract the data from the disk image
$(EXTRACTED_DISK_DIR:$(VERSION)=us): | $(SOTNDISK)
	$(SOTNDISK) extract $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)
$(EXTRACTED_DISK_DIR:$(VERSION)=pspeu) $(EXTRACTED_DISK_DIR:$(VERSION)=hd):
	mkdir -p $(EXTRACTED_DISK_DIR)
	7z x -y $(RETAIL_DISK_DIR)/sotn.pspeu.iso -o$(EXTRACTED_DISK_DIR)
$(EXTRACTED_DISK_DIR:$(VERSION)=saturn):
	bchunk $(RETAIL_DISK_DIR)/sotn.$(VERSION).bin $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue $(RETAIL_DISK_DIR)/sotn.$(VERSION).iso
	7z x $(RETAIL_DISK_DIR)/sotn.$(VERSION).iso01.iso -o$(EXTRACTED_DISK_DIR) || true
extract-disk: $(EXTRACTED_DISK_DIR)

# Targets to create a disk image from build data
ovl_to_bin  = $(1)/$(1).BIN $(1)/F_$(1).BIN
disk_prepare_files := DRA.BIN BIN/RIC.BIN ST/SEL/SEL.BIN
disk_prepare_files += $(addprefix ST/,$(foreach target,$(filter-out sel,$(STAGES)),$(call ovl_to_bin,$(call to_upper,$(target)))))
disk_prepare_files += $(addprefix BOSS/,$(foreach target,$(BOSSES),$(call ovl_to_bin,$(call to_upper,$(target)))))
disk_prepare_files += $(addprefix SERVANT/,$(call to_upper,$(addsuffix .BIN,$(SERVANTS))))
disk-prepare: build $(SOTNDISK)
	$(call echo,Copying extracted disk files) mkdir -p $(BUILD_DISK_DIR); cp -r $(EXTRACTED_DISK_DIR)/* $(BUILD_DISK_DIR)
	$(call echo,Copying main.exe as SLUS_000.67) cp $(BUILD_DIR)/main.exe $(BUILD_DISK_DIR)/SLUS_000.67
	$(foreach item,$(disk_prepare_files),$(call echo,Copying $(item)) cp $(BUILD_DIR)/$(notdir $(item)) $(BUILD_DISK_DIR)/$(item);)
disk-debug: disk-prepare
	cd $(TOOLS_DIR)/sotn-debugmodule && $(MAKE)
	cp $(BUILD_DIR:$(VERSION)=)/sotn-debugmodule.bin $(BUILD_DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK) make $(BUILD_DIR:$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba
disk: disk-prepare
	$(call echo,Creating disk image) $(SOTNDISK) make $(BUILD_DIR:/$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba

# Targets for copying the physical disk to an image file
$(addprefix $(RETAIL_DISK_DIR)/,sotn.%.bin sotn.%.cue): PHONY
	$(muffle)( which -s cdrdao && which -s toc2cue ) || (echo "cdrdao(1) and toc2cue(1) must be installed" && exit 1 )
	$(call echo,Dumping disk)
	$(muffle)cd $(RETAIL_DISK_DIR) && \
        DEVICE="$(shell cdrdao scanbus 2>&1 | grep -vi cdrdao | head -n1 | sed 's/ : [^:]*$$//g')" && \
        cdrdao read-cd \
            --read-raw \
            --datafile sotn.$*.bin \
            --device "$$DEVICE" \
            --driver generic-mmc-raw \
            sotn.$*.toc && \
        toc2cue sotn.$*.toc sotn.$*.cue && \
        rm sotn.$*.toc
$(addprefix dump-disk_,eu hk jp10 jp11 saturn us usproto): $(RETAIL_DISK_DIR)/sotn.$(VERSION).cue
dump-disk_%: PHONY# Last resort
	$(error Automated dumping of $* is not supported)
dump-disk: dump-disk_$(VERSION)

function-finder: graphviz | $(VENV_DIR)
	$(MAKE) clean
	$(MAKE) force-symbols
	$(MAKE) force-extract 
	$(PYTHON) $(TOOLS_DIR)/analyze_calls.py --output_dir=$(TOOLS_DIR)/function_calls/
	git clean -fdxq $(ASM_DIR)/
	git checkout $(CONFIG_DIR)/
	rm -f $(BUILD_DIR)/main.ld $(BUILD_DIR)/weapon.ld
	$(MAKE) extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/function_finder_$(VERSION).py --no-fetch --use-call-trees > $(TOOLS_DIR)/gh-duplicates/functions.md
	-rm -rf $(TOOLS_DIR)/gh-duplicates/function_calls/
	mv $(TOOLS_DIR)/function_calls/ $(TOOLS_DIR)/gh-duplicates/
	mv $(TOOLS_DIR)/function_graphs.md $(TOOLS_DIR)/gh-duplicates/

duplicates-report: | $(VENV_DIR)
	$(MAKE) clean
	$(MAKE) force-symbols
	$(MAKE) force-extract
	$(PYTHON) $(TOOLS_DIR)/function_finder/fix_matchings.py
	mkdir -p $(TOOLS_DIR)/gh-duplicates
	$(DUPS)

# Targets that specify and/or install dependencies
git-submodules: $(ASMDIFFER_APP) $(dir $(M2C_APP)) $(PERMUTER_APP) $(MASPSX_APP) $(MWCCGAP_APP) $(SATURN_SPLITTER_DIR)
update-dependencies: $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) python-dependencies dependencies_$(VERSION) $(SOTNDISK) $(SOTNASSETS) $(SOTNSTR_APP)
	git clean -fdq $(BIN_DIR)/
update-dependencies-all: update-dependencies $(addprefix dependencies_,us pspeu hd saturn)

dependencies_us dependencies_hd: $(MASPSX_APP) 
$(MASPSX_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(MASPSX_APP))

dependencies_pspeu: $(ALLEGREX) $(MWCCGAP_APP) $(MWCCPSP)
$(MWCCGAP_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(MWCCGAP_APP))
$(WIBO):
	$(call wget,https://github.com/decompals/wibo/releases/download/0.6.13/wibo,$@,wibo)
	$(muffle)sha256sum --check $(WIBO).sha256; chmod +x $(WIBO); rm wget-wibo.log
$(MWCCPSP): $(WIBO) $(BIN_DIR)/mwccpsp_219

dependencies_saturn: $(SATURN_SPLITTER_APP) $(ADPCM_EXTRACT_APP) $(DOSEMU_APP) $(CYGNUS)
$(SATURN_SPLITTER_DIR):
	git submodule update --init $(SATURN_SPLITTER_DIR)
$(SATURN_SPLITTER_APP): $(SATURN_SPLITTER_DIR) $(wildcard $(SATURN_SPLITTER_DIR)/rust-dis/src/*)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
$(ADPCM_EXTRACT_APP): $(SATURN_SPLITTER_DIR) $(wildcard $(SATURN_SPLITTER_DIR)/adpcm-extract/src/*)
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release
$(DOSEMU_DIR):
	cd $(TOOLS_DIR); git clone https://github.com/sozud/dosemu-deb.git
$(TOOLS_DIR)/dosemu.make.chkpt: $(DOSEMU_DIR)
	sudo dpkg -i $(TOOLS_DIR)/dosemu-deb/*.deb && touch $@
$(DOSEMU_APP): $(TOOLS_DIR)/dosemu.make.chkpt# This is just a pseudo target because the app binary is older than the repo so it always runs without a checkpoint

$(ASMDIFFER_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(ASMDIFFER_APP))
$(M2C_APP): $(TOOLS_DIR)/python-dependencies.make.chkpt | $(VENV_DIR)
	git submodule update --init $(dir $(M2C_APP))
$(PERMUTER_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(PERMUTER_APP))
$(M2CTX_APP): | $(VENV_DIR)
	$(call wget,https://raw.githubusercontent.com/ethteck/m2ctx/main/m2ctx.py,$@,m2ctx_app)
	$(muffle)rm wget-m2ctx_app.log

$(SOTNSTR_APP): $(TOOLS_DIR)/sotn_str/Cargo.toml $(wildcard $(TOOLS_DIR)/sotn_str/src/*)
	cargo build --release --manifest-path $(TOOLS_DIR)/sotn_str/Cargo.toml
$(SOTNDISK): $(GO) $(wildcard $(SOTNDISK_DIR)/*.go)
	cd $(SOTNDISK_DIR) && $(GO) build
$(SOTNASSETS): $(GO) $(wildcard $(SOTNASSETS_DIR)/*.go)
	cd $(SOTNASSETS_DIR) && $(GO) build
$(GO):
	$(call wget,https://go.dev/dl/go1.22.4.linux-amd64.tar.gz,go1.22.4.linux-amd64.tar.gz,go) && rm wget-go.log
	tar -C $(HOME) -xzf go1.22.4.linux-amd64.tar.gz; rm go1.22.4.linux-amd64.tar.gz

# Since venv is newly created, it can be reasonably assumed that the python requirements need to be installed
$(VENV_DIR):
	$(call echo,Creating python virtual environment) $(SYSTEM_PYTHON) -m venv $(VENV_DIR)
	$(MAKE) python-dependencies
$(TOOLS_DIR)/python-dependencies.make.chkpt: $(TOOLS_DIR)/requirements-python.txt | $(VENV_DIR)
	$(PIP) install -r $(TOOLS_DIR)/requirements-python.txt && touch $@
python-dependencies: $(TOOLS_DIR)/python-dependencies.make.chkpt

$(TOOLS_DIR)/graphviz.make.chkpt: $(TOOLS_DIR)/python-dependencies.make.chkpt
	sudo apt update && sudo apt-get install -y graphviz && touch $@
graphviz: $(TOOLS_DIR)/graphviz.make.chkpt

$(BIN_DIR)/%.tar.gz: $(BIN_DIR)/%.tar.gz.sha256
	$(call wget,https://github.com/Xeeynamo/sotn-decomp/releases/download/cc1-psx-26/$*.tar.gz,$@,$*) 
$(BIN_DIR)/%: $(BIN_DIR)/%.tar.gz
	$(muffle)sha256sum --check $<.sha256
	$(muffle)cd $(BIN_DIR) && tar -xzf $(notdir $<); rm $(notdir $<)
	$(muffle)touch $@; rm wget-$*.log

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

all: ##@  (Default) build and check
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

# .PHONY and .SILENT group
# Putting this in a separate section because if it is included with the targets as I'd prefer, it becomes very cluttered and harder to read.
# These lists can be added to at any point since adding the lists to the actual .PHONY and .SILENT targets is the final action and order does not matter.
# I'd prefer assigning to .PHONY and .SILENT directly without using the list, but the list allows us simply add PHONY_TARGETS to MUFFLED_TARGETS easily instead of duplicating the list.
# They are grouped in the general order you will find the targets in the file.
PHONY: # Since .PHONY reads % as a literal %, we need this target as a prereq to treat pattern targets as .PHONY
PHONY_TARGETS += all clean $(addprefix CLEAN_,$(CLEAN_FILES)) extract build patch check expected
PHONY_TARGETS += dump-disk $(addprefix dump-disk_,eu hk jp10 jp11 saturn us usproto) extract-disk disk disk-prepare disk-debug
PHONY_TARGETS += format-src format-src.run $(addprefix FORMAT_,$(FORMAT_SRC_FILES)) format-tools $(addprefix FORMAT_,$(PY_TOOLS_DIRS))
PHONY_TARGETS += format-symbols format-symbols.run $(addprefix format-symbols_,us hd pspeu saturn) $(addprefix FORMAT_,$(FORMAT_SYMBOLS_FILES)) format-license
PHONY_TARGETS += force-symbols $(addprefix FORCE_,$(FORCE_SYMBOLS)) force-extract context function-finder duplicates-report
PHONY_TARGETS += git-submodules update-dependencies update-dependencies-all $(addprefix dependencies_,us pspeu hd saturn) python-dependencies graphviz $(DOSEMU_APP)
PHONY_TARGETS += help get-debug get-phony get-silent
MUFFLED_TARGETS += $(PHONY_TARGETS) $(MASPSX_APP) $(MWCCGAP_APP) $(MWCCPSP) $(SATURN_SPLITTER_DIR) $(SATURN_SPLITTER_APP) $(EXTRACTED_DISK_DIR) $(ASMDIFFER_APP) $(PERMUTER_APP) $(dir $(M2C_APP)) $(M2C_APP)
MUFFLED_TARGETS += $(DOSEMU_DIR) $(TOOLS_DIR)/dosemu.make.chkpt $(TOOLS_DIR)/python-dependencies.make.chkpt $(TOOLS_DIR)/graphviz.make.chkpt $(SOTNDISK) $(SOTNASSETS) $(VENV_DIR) $(VENV_DIR)
.PHONY: $(PHONY_TARGETS)
# Specifying .SILENT in this manner allows us to set the DEBUG environment variable and display everything for debugging
$(DEBUG).SILENT: $(MUFFLED_TARGETS)
# These are walls of text, so they're redirected to files instead of stdout for debugging
get-debug: get-phony get-silent
get-phony:
	echo ".PHONY:" > make.phony.targets
	$(foreach target,$(PHONY_TARGETS),echo $(target) >> make.phony.targets;)
get-silent:
	echo ".SILENT:" > make.silent.targets
	$(foreach target,$(MUFFLED_TARGETS),echo $(target) >> make.silent.targets;)

# These targets have been renamed, but need to remain usable until CI is updated with the new name.
force_extract: force-extract
	$(info make: warning: force_extract has been renamed to force-extract and will be removed in the future.)
force_symbols: force-symbols
	$(info make: warning: force_symbols has been renamed to force-symbols and will be removed in the future.)
extract_disk: extract-disk
	$(info make: warning: extract_disk has been renamed to extract-disk and will be removed in the future.)
disk_prepare: disk-prepare
	$(info make: warning: disk_prepare has been renamed to disk-prepare and will be removed in the future.)
disk_debug: disk-debug
	$(info make: warning: disk_debug has been renamed to disk-debug and will be removed in the future.)
dump_disk: dump-disk
	$(info make: warning: dump_disk has been renamed to dump-disk and will be removed in the future.)
