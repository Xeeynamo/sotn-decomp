# Game OVL options: main dra ric weapon
# Both stage and reverse stage fall under "STAGES" variable, they are split only for readability.
# Stage OVL options: are cat cen chi dai dre lib mad no0 no1 no2 no3 no4 np3 nz0 nz1 sel st0 top wrp
# Reverse stage OVL options: rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp
# Boss OVL options: bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8
# Servant OVL options: tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006
GAME		:= dra ric
STAGES		:= lib no4 st0 wrp
STAGES		+= 
BOSSES		:= 
SERVANTS	:= tt_000

AS              := $(BIN_DIR)/allegrex-as
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
OPT_HI_FUNCS	:= $(addsuffix .c.o,33F0 A710 C0B0 EC60 186E8 61F30 624DC 628AC 63C90 64EE0) # These objects will get -O4,p instead of -Op
COMPILER		:= $(PYTHON) $(MWCCGAP_APP)
COMPILER_ARGS	 = --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPT_LEVEL)
COMPILER_REQS	:= $(MWCCPSP) $(MWCCGAP_APP) | $(VENV_DIR)/bin
OPT_LEVEL		 = $(if $(filter $(notdir $@),$(OPT_HI_FUNCS)),-O4$(comma)p,-Op)

# Step 1/2 of extract
$(BUILD_DIR:$(VERSION)=pspeu)/%.ld: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt | $(EXTRACTED_DISK_DIR) $(VENV_DIR)/bin
	$(muffle)$(SPLAT) $<

# Step 2/2 of extract
extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,prefixed)))

# Step 1/5 of build
$(BUILD_DIR)/%.s.o: %.s $(AS)# Shared
	$(muffle)$(call echo,Assembling $<,optional)
	$(muffle)mkdir -p $(dir $@); $(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(COMPILER_REQS)# Shared
	$(muffle)$(call echo,Compiling $<,optional)
	$(muffle)mkdir -p $(dir $@); $(COMPILER) $< $(call if_version,pspeu,$@) $(COMPILER_ARGS) $(call if_version,us hd,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	$(muffle)$(call echo,Building $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)mkdir -p $(dir $@); $(LD) -r -b binary -o $@ $<

# Step 2/5 of build
# Todo: This monstrosity of a target should probably be revised, but it works for now
$(addprefix $(BUILD_DIR:$(VERSION)=pspeu)/,$(addsuffix .elf,$(filter-out main,$(GAME)))): $(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.ld $$(call get_functions,%) $$(call list_o_files,%_psp) $$(if $$(filter-out dra,%),$(BUILD_DIR)/assets/%/mwo_header.bin.o)
	$(call link,$*,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/st%.elf: $(BUILD_DIR)/st%.ld $$(call get_functions,%,st) $$(call list_o_files,st/%_psp) $(BUILD_DIR)/assets/st/%/mwo_header.bin.o
	$(call link,st$*,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/bo%.elf: $(BUILD_DIR)/bo%.ld $$(call get_functions,%,bo) $$(call list_o_files,boss/%_psp) $(BUILD_DIR)/assets/boss/%/mwo_header.bin.o
	$(call link,st$*,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call list_o_files,servant/tt_$$*) $(BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link,tt_$*,$@)

# Step 3/5 of build
$(addprefix $(BUILD_DIR)/,%.BIN %.bin %_raw.bin %.exe): $(BUILD_DIR)/$$(call add_ovl_prefix,%,st,bo).elf# Shared
	$(muffle)$(call echo,Building $(notdir $@),optional) $(OBJCOPY) -O binary $< $@

# Step 4/5 of build
$(addsuffix _psp,$(call get_targets)): %_psp: $(BUILD_DIR)/%.bin
	$(call echo,Finished building $*)

# Step 5/5 of build
build_pspeu: $(addsuffix _psp,$(call get_targets))

PHONY_TARGETS += extract_pspeu build_pspeu $(addsuffix _psp,$(call get_targets))
MUFFLED_TARGETS += $(addprefix $(BUILD_DIR:$(VERSION)=pspeu)/,$(addsuffix .elf,$(filter-out main,$(GAME))))
# Muffled in target:
# $(BUILD_DIR:$(VERSION)=pspeu)/%.ld
# $(BUILD_DIR)/%.s.o $(BUILD_DIR)/%.c.o $(BUILD_DIR)/assets/%/mwo_header.bin.o
# $(addprefix $(BUILD_DIR)/%,.BIN .bin _raw.bin .exe)
# Muffled in link function:
# $(BUILD_DIR:$(VERSION)=pspeu)/st%.elf $(BUILD_DIR:$(VERSION)=pspeu)/bo%.elf $(BUILD_DIR:$(VERSION)=pspeu)/tt_%.elf
