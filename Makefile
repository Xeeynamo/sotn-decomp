.SECONDEXPANSION:
.SECONDARY:
.DEFAULT_GOAL := all
PHONY_TARGETS := # Empty variable
MUFFLED_TARGETS := # Empty variable

VERSION		?= us# Only when env not set
VENV_DIR	?= .venv# Can be overriden with env
comma		:= ,# For escaping a literal comma
muffle 		:= $(if $(VERBOSE),,@)# Allows VERBOSE to unmuffle targets which can't use .SILENT

# Utility functions
rwildcard	= $(subst //,/,$(foreach dir,$(wildcard $(1:=/*)),$(call rwildcard,$(dir),$(2)) $(filter $(subst *,%,$(2)),$(dir))))
to_upper	= $(shell echo $(1) | tr '[:lower:]' '[:upper:]')
to_lower	= $(shell echo $(1) | tr '[:upper:]' '[:lower:]')
if_version	= $(if $(filter $(1),$(VERSION)),$(2),$(3))
# Use $(call get_targets,prefixed) when stages and bosses need to be prefixed
get_targets = $(GAME) $(addprefix $(if $(1),st),$(STAGES)) $(addprefix $(if $(1),bo),$(BOSSES)) $(SERVANTS)

# System related variables
OS 				:= $(or $(filter $(call to_lower,$(shell uname -s),linux darwin),linux))# Default to linux if it isn't linux or darwin
ARCH			:= $(subst x86_64,amd64,$(shell uname -m))
SYSTEM_PYTHON	:= $(or $(shell which python),/usr/bin/python3)# Only used for installing venv
PYTHON_BIN		:= $(or $(realpath $(VENV_DIR)/bin/))
PYTHON          := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)python3# This is slightly redundant to handle the slash
PIP			 	:= $(VENV_DIR)/bin/pip3# Pip will always use venv
BASH			:= $(or $(shell which bash),/usr/bin/bash)
BASH_FLAGS	  	:= -e -o pipefail
SHELL 			:= $(BASH) $(BASH_FLAGS)

# Directories
ASM_DIR         := asm/$(VERSION)
ASM_SUBDIRS 	:= data/ $(call if_version,us hd,psxsdk/ handwritten/)
SRC_SUBDIRS 	:= $(call if_version,us hd,psxsdk/)
ASSETS_DIR      := assets
CONFIG_DIR      := config
BUILD_DIR       := build/$(VERSION)
EXTRACTED_DISK_DIR := disks/$(VERSION:hd=pspeu)
BUILD_DISK_DIR  := $(BUILD_DIR)/disk

# Files
CHECK_FILES 	:= $(shell cut -d' ' -f3 $(CONFIG_DIR)/check.$(VERSION).sha)
ST_ASSETS		:= D_801*.bin *.gfxbin *.palbin cutscene_*.bin

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
ALLEGREX 		:= bin/allegrex-as
WIBO            := bin/wibo
MWCCPSP         := bin/mwccpsp.exe
CYGNUS			:= bin/cygnus-2.7-96Q3-bin
CC1_SATURN		:= $(BUILD_DIR)/CC1.EXE

# Symbols
BASE_SYMBOLS	 = $(CONFIG_DIR)/symbols.$(if $(filter mad,$(1)),beta,$(VERSION)).txt
UNDEFINED_SYMS 	 = $(CONFIG_DIR)/undefined_syms.$(if $(filter stmad,$(1)),beta,$(VERSION)).txt
AUTO_UNDEFINED	 = TYPE_auto$(if $(filter-out stmad,$(1)),.$(VERSION)).$(1).txt

# Other tooling
BLACK			:= $(and $(PYTHON_BIN),$(PYTHON_BIN)/)black
SPLAT           := $(and $(PYTHON_BIN),$(PYTHON_BIN)/)splat split
ICONV           := iconv --from-code=UTF-8 --to-code=Shift-JIS
DIRT_PATCHER    := $(PYTHON) tools/dirt_patcher.py
SHASUM          := shasum
GFXSTAGE        := $(PYTHON) tools/gfxstage.py
PNG2S           := $(PYTHON) tools/png2s.py
CLANG			:= bin/clang-format
GO              := $(HOME)/go/bin/go
SOTNLINT		:= cargo run --release --manifest-path tools/lints/sotn-lint/Cargo.toml src/
SOTNSTR_APP     := tools/sotn_str/target/release/sotn_str
ASMDIFFER_APP	:= tools/asm-differ/diff.py
M2CTX_APP       := tools/m2ctx.py
M2C_APP         := tools/m2c/m2c.py
PERMUTER_APP	:= tools/decomp-permuter
MASPSX_APP      := tools/maspsx/maspsx.py
MWCCGAP_APP     := tools/mwccgap/mwccgap.py
DOSEMU_DIR		:= tools/dosemu-deb
DOSEMU_APP		:= $(or $(shell which dosemu),/usr/bin/dosemu)
SATURN_SPLITTER_DIR := tools/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract
SOTNDISK_APP        := tools/sotn-disk/sotn-disk
SOTNASSETS_APP      := tools/sotn-assets/sotn-assets

# Build functions
define get_src_files
	$(foreach dir,$(ASM_DIR)/$(1)/ $(addprefix $(ASM_DIR)/$(1)/,$(ASM_SUBDIRS)),$(wildcard $(dir)/*.s))
	$(foreach dir,src/$(1)/ $(addprefix src/$(1)/,$(if $(2),,$(SRC_SUBDIRS))),$(wildcard $(dir)/*.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(if $(2),$(addprefix $(dir)/,$(ST_ASSETS)),$(dir)/*)))
endef
get_shared_src_files = $(foreach dir,src/$(1),$(wildcard $(dir)/*.c))
# sel doesn't follow the same pattern as other stages, so we ignore $(2) for it in get_o_files/get_src_files
2_IGNORE_SEL = $(if $(filter-out st/sel,$(1)),$(2))
get_o_files = $(subst //,/,$(foreach file,$(call get$(3)_src_files,$(1),$(2_IGNORE_SEL)),$(BUILD_DIR)/$(file).o))
define link
	$(muffle)echo -e "Linking $(1)"
	$(muffle)$(LD) $(LD_FLAGS) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(BUILD_DIR)/$(1).ld \
		$(call if_version,pspeu,-T $(CONFIG_DIR)/symexport.$(VERSION).$(1).txt) \
		$(if $(wildcard $(UNDEFINED_SYMS)),-T $(UNDEFINED_SYMS)) \
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
get_psp_o_files = $(subst //,/,$(call get_merged_o_files,$(1),$(2)) $(call get_o_files,$(2)/$(1)_psp) $(if $(filter-out dra,$(1)),$(BUILD_DIR)/assets/$(2)/$(1)/mwo_header.bin.o))
get_build_dirs = $(subst //,/,$(addsuffix /,$(addprefix $(BUILD_DIR)/,$(1))))
get_ovl_from_path = $(word $(or $(2),1),$(filter $(call get_targets),$(subst /, ,$(1))))
add_ovl_prefix = $(if $(filter $(call to_lower,$(1)),$(STAGES)),$(or $(2),st),$(if $(filter $(call to_lower,$(1)),$(BOSSES)),$(or $(3),bo)))$(call to_lower,$(1))

all: build check
extract: extract.$(VERSION)
build: build.$(VERSION)

clean:
	git clean -fdxq $(ASSETS_DIR)/ $(ASM_DIR)/ $(BUILD_DIR)/ src/weapon/ $(CONFIG_DIR)/*$(VERSION)*
	git clean -fdxq function_calls/ sotn_calltree.txt

FORMAT_SRC_IGNORE	:= $(call rwildcard,src/pc/3rd/,*)
FORMAT_SRC_FILES	:= $(filter-out $(FORMAT_SRC_IGNORE),$(call rwildcard,src/ include/,*.c *.h))
format-src.run:# For output control and progress tracking in the event of an error
	$(muffle)mkdir -p /tmp/sotn-decomp && rm /tmp/sotn-decomp/$@ > /dev/null 2>&1 || true
	$(muffle)echo -e "Running clang to format src/* and include/* (this may take some time)"
$(addsuffix .format-src,$(FORMAT_SRC_FILES)): %.format-src: format-src.run $(CLANG)
	$(muffle)echo "$*" >> /tmp/sotn-decomp/$<; $(CLANG) -i $*
format-src: $(addsuffix .format-src,$(FORMAT_SRC_FILES))# Appends .format-src for deconfliction and runs each file individually in order to leverage the -j option
# Redirecting sotn-lint stdout because even if there was something useful, you'd never see it because of the output spam
	$(SOTNLINT) 1>/dev/null

format-tools:
	$(BLACK) *.py tools/*.py tools/sotn_permuter/permuter_loader.py tools/function_finder/*.py tools/splat_ext/*.py tools/split_jpt_yaml/*.py

FORMAT_SYMBOLS_IGNORE	:= $(foreach version,us pspeu hd saturn,$(addprefix $(CONFIG_DIR)/,splat.$(version).weapon.yaml assets.$(version).yaml assets.$(version).yaml))
FORMAT_SYMBOLS_FILES	:= $(filter-out $(FORMAT_SYMBOLS_IGNORE),$(wildcard $(CONFIG_DIR)/*.yaml))
$(addsuffix .format-symbols,$(FORMAT_SYMBOLS_FILES)): %.format-symbols: | $(VENV_DIR)
	$(muffle)echo -e "Removing orphan symbols using $*"
	$(muffle)$(PYTHON) tools/symbols.py remove-orphans $*
$(addsuffix .format-symbols,us pspeu hd saturn): %.format-symbols: | $(VENV_DIR)
	$(muffle)echo -e "Sorting $* symbols"
	$(muffle)VERSION=$* $(PYTHON) tools/symbols.py sort
format-symbols: $(addsuffix .format-symbols,us pspeu hd saturn $(FORMAT_SYMBOLS_FILES))

format-license:
	find src/ -type f -name "*.c" -or -name "*.h" | grep -vE 'PsyCross|mednafen|psxsdk|3rd|saturn/lib' | $(PYTHON) tools/lint-license.py - AGPL-3.0-or-later
	$(PYTHON) tools/lint-license.py include/game.h AGPL-3.0-or-later
	$(PYTHON) tools/lint-license.py include/entity.h AGPL-3.0-or-later
	$(PYTHON) tools/lint-license.py include/items.h AGPL-3.0-or-later
	$(PYTHON) tools/lint-license.py include/lba.h AGPL-3.0-or-later
	$(PYTHON) tools/lint-license.py include/memcard.h AGPL-3.0-or-later

format: format-tools format-symbols format-license
	$(MAKE) -j format-src

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
expected: check
	rm -rf expected/$(BUILD_DIR) > /dev/null 2>&1 || true
	$(muffle)mkdir -p expected
	cp -r $(BUILD_DIR) expected/$(BUILD_DIR)

force-extract:
	mkdir -p /tmp/sotn-decomp
	rm -rf /tmp/sotn-decomp/src || true; mv src /tmp/sotn-decomp/src
	find $(BUILD_DIR) -type f -name "*.ld" -delete || true
	$(MAKE) extract
	rm -rf src/
	mv /tmp/sotn-decomp/src src/
force-extract-disk:
	rm -rf $(EXTRACTED_DISK_DIR) > /dev/null 2>&1 || true
	$(MAKE) extract-disk
# This is currently intentionally hard coded to us because the us symbols files are used for finding functions in other versions
$(addsuffix .force-symbols,$(notdir $(wildcard $(BUILD_DIR:$(VERSION)=us)/*.elf))): %.elf.force-symbols: | $(VENV_DIR)
	$(PYTHON) tools/symbols.py elf $(BUILD_DIR)/$*.elf > $(CONFIG_DIR)/symbols$(if $(filter-out stmad,$*),.us).$*.txt
force-symbols: $(addsuffix .force-symbols,$(notdir $(wildcard $(BUILD_DIR:$(VERSION)=us)/*.elf)))

context: $(M2CTX_APP) | $(VENV_DIR)
ifndef SOURCE
	$(error SOURCE environment variable must be set to generate context)
endif
	VERSION=$(VERSION) $(PYTHON) $(M2CTX_APP) $(SOURCE)
	$(muffle)echo "ctx.c has been updated."

disks/us: | $(SOTNDISK_APP)
	$(SOTNDISK_APP) extract disks/sotn.$(VERSION).cue $(EXTRACTED_DISK_DIR)
disks/pspeu:
	mkdir -p $(EXTRACTED_DISK_DIR)
	7z x -y disks/sotn.pspeu.iso -o$(EXTRACTED_DISK_DIR)
disks/saturn:
	bchunk disks/sotn.$(VERSION).bin disks/sotn.$(VERSION).cue disks/sotn.$(VERSION).iso
	7z x disks/sotn.$(VERSION).iso01.iso -o$(EXTRACTED_DISK_DIR) || true
extract-disk: $(EXTRACTED_DISK_DIR)

ovl_to_bin  = $(call to_upper,$(call add_ovl_prefix,$(1),ST/,BOSS/)/$(1).BIN $(call add_ovl_prefix,$(1),ST/,BOSS/)/F_$(1).BIN)
DISK_PREPARE_FILES := DRA.BIN BIN/RIC.BIN ST/SEL/SEL.BIN $(addprefix SERVANT/,$(call to_upper,$(addsuffix .BIN,$(SERVANTS))))
DISK_PREPARE_FILES += $(foreach target,$(filter-out sel,$(STAGES)) $(BOSSES),$(call ovl_to_bin,$(target)))
disk-prepare: build $(SOTNDISK_APP)
	mkdir -p $(BUILD_DISK_DIR); cp -r $(EXTRACTED_DISK_DIR)/* $(BUILD_DISK_DIR)
	cp $(BUILD_DIR)/main.exe $(BUILD_DISK_DIR)/SLUS_000.67
	$(muffle)echo "cp $(BUILD_DIR)/*.BIN $(BUILD_DISK_DIR)/<OVL_PATH>"; $(foreach item,$(DISK_PREPARE_FILES),cp $(BUILD_DIR)/$(notdir $(item)) $(BUILD_DISK_DIR)/$(item);)
disk-debug: disk-prepare
	cd tools/sotn-debugmodule && $(MAKE)
	cp $(BUILD_DIR:$(VERSION)=)/sotn-debugmodule.bin $(BUILD_DISK_DIR)/SERVANT/TT_000.BIN
	$(SOTNDISK_APP) make $(BUILD_DIR:$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba
disk: disk-prepare
	$(SOTNDISK_APP) make $(BUILD_DIR:/$(VERSION)=)/sotn.$(VERSION).cue $(BUILD_DISK_DIR) $(CONFIG_DIR)/disk.$(VERSION).lba

# Targets for copying the physical disk to an image file
$(addprefix disks/,sotn.%.bin sotn.%.cue): PHONY
	$(muffle)( which -s cdrdao && which -s toc2cue ) || (echo "cdrdao(1) and toc2cue(1) must be installed" && exit 1 )
	$(muffle)echo "Dumping disk"
	$(muffle)cd disks && \
        DEVICE="$(shell cdrdao scanbus 2>&1 | grep -vi cdrdao | head -n1 | sed 's/ : [^:]*$$//g')" && \
        cdrdao read-cd \
            --read-raw \
            --datafile sotn.$*.bin \
            --device "$$DEVICE" \
            --driver generic-mmc-raw \
            sotn.$*.toc && \
        toc2cue sotn.$*.toc sotn.$*.cue && \
        rm sotn.$*.toc
$(addprefix dump-disk,.eu .hk .jp10 .jp11 .saturn .us .usproto): disks/sotn.$(VERSION).cue
dump-disk.%: PHONY# Last resort
	$(error Automated dumping of $* is not supported)
dump-disk: dump-disk.$(VERSION)

# Targets that specify and/or install dependencies
git-submodules: $(ASMDIFFER_APP) $(dir $(M2C_APP)) $(PERMUTER_APP) $(MASPSX_APP) $(MWCCGAP_APP) $(SATURN_SPLITTER_DIR)
update-dependencies: $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) python-dependencies dependencies.$(VERSION) $(SOTNDISK_APP) $(SOTNASSETS_APP) $(SOTNSTR_APP) $(CLANG) $(GO)
	git clean -fdq bin/
update-dependencies-all: update-dependencies $(addprefix dependencies,.us .pspeu .hd .saturn)

dependencies.us dependencies.hd: $(MASPSX_APP) 
$(MASPSX_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(MASPSX_APP))

dependencies.pspeu: $(ALLEGREX) $(MWCCGAP_APP) $(MWCCPSP)
$(MWCCGAP_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(MWCCGAP_APP))
$(WIBO):
	curl -sSfL -o $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	$(muffle)sha256sum --check $(WIBO).sha256; chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) bin/mwccpsp_219

dependencies.saturn: $(SATURN_SPLITTER_APP) $(ADPCM_EXTRACT_APP) $(DOSEMU_APP) $(CYGNUS)
$(SATURN_SPLITTER_DIR)%:
	git submodule update --init $(SATURN_SPLITTER_DIR)
$(SATURN_SPLITTER_APP): $(SATURN_SPLITTER_DIR) $(SATURN_SPLITTER_DIR)/rust-dis/Cargo.toml $(wildcard $(SATURN_SPLITTER_DIR)/rust-dis/src/*)
	cargo build --release --manifest-path $(SATURN_SPLITTER_DIR)/rust-dis/Cargo.toml
$(ADPCM_EXTRACT_APP): $(SATURN_SPLITTER_DIR) $(SATURN_SPLITTER_DIR)/adpcm-extract/Cargo.toml $(wildcard $(SATURN_SPLITTER_DIR)/adpcm-extract/src/*)
	cargo build --release --manifest-path $(SATURN_SPLITTER_DIR)/adpcm-extract/Cargo.toml
$(DOSEMU_DIR):
	cd tools; git clone https://github.com/sozud/dosemu-deb.git
tools/dosemu.make.chkpt: $(DOSEMU_DIR)
	sudo dpkg -i tools/dosemu-deb/*.deb && touch $@
$(DOSEMU_APP): tools/dosemu.make.chkpt# This is just a pseudo target because the app binary is older than the repo so it always runs without a checkpoint

$(ASMDIFFER_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(ASMDIFFER_APP))
$(M2C_APP): tools/python-dependencies.make.chkpt | $(VENV_DIR)
	git submodule update --init $(dir $(M2C_APP))
$(PERMUTER_APP): | $(VENV_DIR)
	git submodule update --init $(dir $(PERMUTER_APP))

$(SOTNSTR_APP): tools/sotn_str/Cargo.toml $(wildcard tools/sotn_str/src/*)
	cargo build --release --manifest-path tools/sotn_str/Cargo.toml
$(SOTNDISK_APP): $(GO) $(wildcard $(dir $(SOTNDISK_APP))/*.go)
	cd $(dir $(SOTNDISK_APP)) && $(GO) build
$(SOTNASSETS_APP): $(GO) $(wildcard $(dir $(SOTNASSETS_APP))/*.go)
	cd $(dir $(SOTNASSETS_APP)) && $(GO) build

# Since venv is newly created, it can be reasonably assumed that the python requirements need to be installed
$(VENV_DIR):
	echo -e "Creating python virtual environment"
	$(SYSTEM_PYTHON) -m venv $(VENV_DIR)
	$(MAKE) python-dependencies
tools/python-dependencies.make.chkpt: tools/requirements-python.txt | $(VENV_DIR)
	$(PIP) install -r tools/requirements-python.txt && touch $@
python-dependencies: tools/python-dependencies.make.chkpt

tools/graphviz.make.chkpt: tools/python-dependencies.make.chkpt
	sudo apt update && sudo apt-get install -y graphviz && touch $@
graphviz: tools/graphviz.make.chkpt

$(GO):
	curl -sSfL -O https://go.dev/dl/go1.22.4.$(OS)-$(ARCH).tar.gz
	$(muffle)tar -C $(HOME) -xzf go1.22.4.$(OS)-$(ARCH).tar.gz; rm go1.22.4.$(OS)-$(ARCH).tar.gz
bin/%.tar.gz: bin/%.tar.gz.sha256
	curl -sSfL -o $@ https://github.com/Xeeynamo/sotn-decomp/releases/download/cc1-psx-26/$*.tar.gz
bin/%: bin/%.tar.gz
	$(muffle)sha256sum --check $<.sha256
	$(muffle)cd bin/ && tar -xzf $(notdir $<); rm $(notdir $<)
	$(muffle)touch $@

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
PHONY_TARGETS += all extract build patch check 
PHONY_TARGETS += dump-disk $(addprefix dump-disk.,eu hk jp10 jp11 saturn us usproto) extract-disk
PHONY_TARGETS += format-src format-src.run $(addsuffix .format-src,$(FORMAT_SRC_FILES)) format-tools format-symbols format-license
PHONY_TARGETS += $(addsuffix .force-symbols,$(notdir $(wildcard $(BUILD_DIR:$(VERSION)=us)/*.elf))) force-extract $(addprefix format-symbols.,us hd pspeu saturn $(FORMAT_SYMBOLS_FILES))
PHONY_TARGETS += git-submodules update-dependencies update-dependencies-all $(addprefix dependencies.,us pspeu hd saturn) python-dependencies graphviz $(DOSEMU_APP)
PHONY_TARGETS += help get-debug get-phony get-silent
MUFFLED_TARGETS += $(PHONY_TARGETS) $(MASPSX_APP) $(MWCCGAP_APP) $(MWCCPSP) $(SATURN_SPLITTER_DIR) $(SATURN_SPLITTER_APP) $(EXTRACTED_DISK_DIR) $(ASMDIFFER_APP) $(PERMUTER_APP) $(dir $(M2C_APP)) $(M2C_APP)
MUFFLED_TARGETS += $(DOSEMU_DIR) tools/dosemu.make.chkpt tools/python-dependencies.make.chkpt tools/graphviz.make.chkpt $(SOTNDISK_APP) $(SOTNASSETS_APP) $(VENV_DIR) $(VENV_DIR)
.PHONY: $(PHONY_TARGETS) expected clean force-symbols disk disk-prepare disk-debug context
# Specifying .SILENT in this manner allows us to set the VERBOSE environment variable and display everything for debugging
$(VERBOSE).SILENT: $(MUFFLED_TARGETS)

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
