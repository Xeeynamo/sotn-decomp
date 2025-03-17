AS              := $(BIN_DIR)/allegrex-as
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
OPT_HI_FUNCS	:= $(addsuffix .c.o,33F0 A710 C0B0 EC60 186E8 61F30 624DC 628AC 63C90 64EE0) # These objects will get -O4,p instead of -Op
COMPILER		 = $(SOTNSTR) process -f $< | $(PYTHON) $(MWCCGAP_APP)
COMPILER_REQS	:= $(MWCCPSP) $(MWCCGAP_APP) | $(VENV_DIR)/bin
COMPILER_ARGS	 = --src-dir $(dir $<) --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --target-encoding sjis --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPT_LEVEL) -opt nointrinsics
OPT_LEVEL		 = $(if $(filter $(notdir $@),$(OPT_HI_FUNCS)),-O4$(comma)p,-Op)
LD_FLAGS 		:= --gc-sections

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
	$(muffle)mkdir -p $(dir $@); $(COMPILER) $(call if_version,pspeu,$@) $(COMPILER_ARGS) $(call if_version,us hd,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	$(muffle)$(call echo,Building $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)mkdir -p $(dir $@); $(LD) -r -b binary -o $@ $<

# Step 2/5 of build
# Todo: This monstrosity of a target should probably be revised, but it works for now
$(addprefix $(BUILD_DIR:$(VERSION)=pspeu)/,$(addsuffix .elf,$(filter-out main,$(GAME)))): $(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.ld $$(call get_functions,%) $$(call get_o_files,%_psp) $$(if $$(filter-out dra,%),$(BUILD_DIR)/assets/%/mwo_header.bin.o)
	$(call link,$*,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/st%.elf: $(BUILD_DIR)/st%.ld $$(call get_functions,%,st) $$(call get_o_files,st/%_psp) $(BUILD_DIR)/assets/st/%/mwo_header.bin.o
	$(call link,st$*,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/bo%.elf: $(BUILD_DIR)/bo%.ld $$(call get_functions,%,bo) $$(call get_o_files,boss/%_psp) $(BUILD_DIR)/assets/boss/%/mwo_header.bin.o
	$(call link,st$*,$@)
$(BUILD_DIR:$(VERSION)=pspeu)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call get_o_files,servant/tt_$$*) $(BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link,tt_$*,$@)

# Step 3/5 of build
$(addprefix $(BUILD_DIR)/,%.BIN %.bin %_raw.bin %.exe): $(BUILD_DIR)/$$(call add_ovl_prefix,%).elf# Shared
	$(muffle)$(call echo,Building $(notdir $@),optional) $(OBJCOPY) -O binary $< $@

# Step 4/5 of build
$(addsuffix _psp,$(call get_targets)): %_psp: $(BUILD_DIR)/%.bin
	$(call echo,Finished building $*)

# Step 5/5 of build
build_pspeu: $(addsuffix _psp,$(call get_targets))

PHONY_TARGETS += extract_pspeu build_pspeu $(addsuffix _psp,$(call get_targets))
MUFFLED_TARGETS += $(addprefix $(BUILD_DIR:$(VERSION)=pspeu)/,$(addsuffix .elf,$(filter-out main,$(GAME))))
