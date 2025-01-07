# Configuration
BUILD_DIR       := build/pspeu
PSP_EU_TARGETS  := dra stst0 stwrp tt_000

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

SPLAT_PIP       := splat split

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

# Targets
build_pspeu: $(addsuffix _psp,$(PSP_EU_TARGETS))

extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSP_EU_TARGETS)))

$(WIBO):
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check $(WIBO).sha256
	chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) $(BIN_DIR)/mwccpsp_219

$(MWCCGAP_APP):
	git submodule init $(MWCCGAP_DIR)
	git submodule update $(MWCCGAP_DIR)

dra_psp: $(BUILD_DIR)/dra.bin
tt_000_psp: $(BUILD_DIR)/tt_000.bin
stst0_psp: $(BUILD_DIR)/st0.bin
stwrp_psp: $(BUILD_DIR)/wrp.bin

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/st0.bin: $(BUILD_DIR)/stst0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/wrp.bin: $(BUILD_DIR)/stwrp.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/dra.ld: $(CONFIG_DIR)/splat.pspeu.dra.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.dra.txt
	$(SPLAT_PIP) $<
$(BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.pspeu.st%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.st%.txt
	$(SPLAT_PIP) $<
$(BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.pspeu.tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.tt_%.txt
	$(SPLAT_PIP) $<

ST_DRA_MERGE = 624DC 628AC
$(BUILD_DIR)/dra.elf: $(BUILD_DIR)/dra.ld $(addprefix $(BUILD_DIR)/src/dra/,$(addsuffix .c.o,$(ST_DRA_MERGE))) $$(call list_o_files_psp,dra_psp)
	$(call link_with_deadstrip,dra,$@)
$(BUILD_DIR)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call list_o_files_psp,servant/tt_$$*) $(BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link_with_deadstrip,tt_$*,$@)

ST_ST0_MERGE = title_card popup e_room_fg st_common
$(BUILD_DIR)/stst0.elf: $(BUILD_DIR)/stst0.ld $(addprefix $(BUILD_DIR)/src/st/st0/,$(addsuffix .c.o,$(ST_ST0_MERGE))) $$(call list_o_files_psp,st/st0_psp) $(BUILD_DIR)/assets/st/st0/mwo_header.bin.o
	$(call link_with_deadstrip,stst0,$@)
ST_WRP_MERGE = st_update e_particles e_room_fg st_common st_debug e_breakable popup warp e_red_door
$(BUILD_DIR)/stwrp.elf: $(BUILD_DIR)/stwrp.ld $(addprefix $(BUILD_DIR)/src/st/wrp/,$(addsuffix .c.o,$(ST_WRP_MERGE))) $$(call list_o_files_psp,st/wrp_psp) $(BUILD_DIR)/assets/st/wrp/mwo_header.bin.o
	$(call link_with_deadstrip,stwrp,$@)

# Recipes
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

# Much of DRA has O4. Here we set optimization of the overlay - DRA gets O4, otherwise Op.
OPT_HIGH = -O4,p #need this because otherwise the comma breaks the if-statement
OPT_OVL = $(if $(findstring dra, $@), $(OPT_HIGH), -Op)
# Allow override. Any file in this list will get Op.
OPT_LO_OVERRIDES = 67F0.c.o 86A0.c.o 22A40.c.o 23FE0.c.o 32DA0.c.o 3AE30.c.o 60D80.c.o 60F10.c.o
OPTIMIZATION = $(if $(filter $(notdir $@),$(OPT_LO_OVERRIDES)), -Op, $(OPT_OVL))

$(BUILD_DIR)/%.c.o: %.c $(MWCCPSP) $(MWCCGAP_APP)
	@mkdir -p $(dir $@)
	$(MWCCGAP) $< $@ --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPTIMIZATION)

$(BUILD_DIR)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<
