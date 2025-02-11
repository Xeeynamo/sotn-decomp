.SECONDEXPANSION:
.SECONDARY:

# Variables
# User environment
ifeq ($(VERSION),)
$(info VERSION not defined, defaulting to VERSION=us)
VERSION         ?= us
endif

# Game OVL options: main dra ric weapon
# Both stage and reverse stage fall under "STAGES" variable, they are split only for readability.
# Stage OVL options: no0 no1 lib cat no2 chi dai np3 cen no4 are top nz0 nz1 wrp dre st0 no3 mad sel
# Reverse stage OVL options: rno0 rno1 rlib rcat rno2 rchi rdai rno3 rcen rno4 rare rtop rnz0 rnz1 rwrp
# Boss OVL options: bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8
# Weapon OVL options: tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006

ifeq ($(VERSION),us)
VERSION_PREFIX 	:= PSX_US
PSX_US_GAME		:= main dra ric weapon
PSX_US_STAGES	:= cen chi dre lib no0 no1 no3 np3 nz0 st0 wrp mad sel no4
PSX_US_STAGES   += rwrp # Second line for stages for future readability
PSX_US_BOSSES	:= mar rbo3
PSX_US_SERVANT	:= tt_000 tt_001 tt_002 tt_003 tt_004
else ifeq ($(VERSION),hd)
VERSION_PREFIX	:= PSX_HD
PSX_HD_GAME		:= dra ric
PSX_HD_STAGES	:= cen wrp
PSX_HD_STAGES	+= 
PSX_HD_BOSSES	:= 
PSX_HD_SERVANTS	:= tt_000
else ifeq ($(VERSION),pspeu)
VERSION_PREFIX 	:= PSP_EU
PSP_EU_GAME		:= dra
PSP_EU_STAGES	:= lib st0 wrp no4
PSP_EU_STAGES	+= 
PSP_EU_BOSSES	:= 
PSP_EU_SERVANTS	:= tt_000
else ifeq ($(VERSION),saturn) # Saturn is special and does not yet conform
VERSION_PREFIX 	:= SATURN
SATURN_GAME		:= GAME ALUCARD
SATURN_STAGES	:= STAGE_02 WARP
SATURN_STAGES	+= 
SATURN_BOSSES 	:= 
SATURN_SERVANTS	:= T_BAT
endif

# Extract targets is for when stages and bosses need to be prefixed with st and bo respectively
$(VERSION_PREFIX)_EXTRACT_TARGETS	:= $($(VERSION_PREFIX)_GAME) $(addprefix st,$($(VERSION_PREFIX)_STAGES)) $(addprefix bo,$($(VERSION_PREFIX)_BOSSES)) $($(VERSION_PREFIX)_SERVANTS)
# Build targets is for when the non-prefixed name is needed
$(VERSION_PREFIX)_BUILD_TARGETS	:= $($(VERSION_PREFIX)_GAME) $($(VERSION_PREFIX)_STAGES) $($(VERSION_PREFIX)_BOSSES) $($(VERSION_PREFIX)_SERVANTS)

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
BASE_SYMBOLS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

# Lists of functions that have been matched across multiple versions
ST_DRA_MERGE := $(file < $(CONFIG_DIR)/merge.dra.txt) 
ST_LIB_MERGE := $(file < $(CONFIG_DIR)/merge.lib.txt)
ST_ST0_MERGE := $(file < $(CONFIG_DIR)/merge.st0.txt)
ST_WRP_MERGE := $(file < $(CONFIG_DIR)/merge.wrp.txt)
ST_NO4_MERGE := $(file < $(CONFIG_DIR)/merge.no4.txt)

# Tooling
SHELL 			 = /bin/bash -e -o pipefail
VENV_DIR       	?= .venv
PYTHON_BIN		:= $(VENV_DIR)/bin
PYTHON          := $(PYTHON_BIN)/python3
PIP				:= $(PYTHON_BIN)/pip3
SPLAT           := splat split
#MAKEFLAGS 		+= --jobs
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

# Files and file lists
SOTNDISK_SOURCES	:= $(wildcard $(addsuffix /*.go, $(TOOLS_DIR)))
SOTNASSETS_SOURCES	:= $(wildcard $(addsuffix /*.go, $(TOOLS_DIR)))

CHECK_FILES := $(shell cut -d' ' -f3 config/check.$(VERSION).sha)

# Dependencies
DEPENDENCIES	= $(ASMDIFFER_APP) $(M2CTX_APP) $(M2C_APP) $(GO) git-dependencies debian-dependencies python-dependencies

# Platform specific variables
ifneq ($(filter $(VERSION),us hd),) # Both us and hd versions use the PSX platform
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

DEPENDENCIES	+= $(MASPSX_APP) 
else ifeq ($(VERSION),pspeu)
# Flags
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
MWLDPSP_FLAGS   := -partial -nostdlib -msgstyle gcc -sym full,elf -g
# Most of PSP is compiled with -O0, except part of DRA. This block selects the proper flag.
OPT_HIGH 		= -O4,p #need this because otherwise the comma breaks the if-statement
# Allow override. Any file in this list will get O4.
OPT_HI_OVERRIDES = 33F0.c.o A710.c.o C0B0.c.o EC60.c.o 186E8.c.o 61F30.c.o 624DC.c.o 628AC.c.o 63C90.c.o 64EE0.c.o
OPTIMIZATION = $(if $(filter $(notdir $@),$(OPT_HI_OVERRIDES)), $(OPT_HIGH), -Op)

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

DEPENDENCIES	+= $(ALLEGREX_AS)
else ifeq ($(VERSION),saturn)
SATURN_SPLITTER_DIR			:= $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP 		:= $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
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
DEPENDENCIES			+= $(SATURN_SPLITTER_APP)
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

include Makefile.tools.mk
ifneq (,$(filter $(VERSION),us hd)) # Both us and hd versions use the PSX platform
include Makefile.psx.mk
else ifeq ($(VERSION),pspeu)
include Makefile.psp.mk
else ifeq ($(VERSION),saturn)
include Makefile.saturn.mk
endif
