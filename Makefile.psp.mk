AS              := $(ALLEGREX)
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -DSOTN_STR -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
LD_FLAGS		:= --gc-sections
CCPSP           := MWCIncludes=$(BIN_DIR) $(WIBO) $(MWCCPSP)
OPT_HI_LIST		:= $(addsuffix .c.o, 80 1E50 33F0 A710 C0B0 E6A8 186E8 26948 61F30 624DC 628AC 62FE0 63C90 64EE0)# These objects will get -O4,p instead of -Op
OPT_LEVEL		 = $(if $(filter $(notdir $@),$(OPT_HI_LIST)),-O4$(comma)p,-Op)
COMPILER_ARGS	 = --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --target-encoding sjis --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPT_LEVEL) -opt nointrinsics
AUTO_MERGE_FILES	:= e_init.c

# Step 1/2 of extract
$(BUILD_DIR)/%.ld assets/%/mwo_header.bin: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt | $(EXTRACTED_DISK_DIR) $(VENV_DIR)
	$(muffle)$(SPLAT) $<

# Step 2/2 of extract
extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,prefixed)))

# Step 1/5 of build
$(BUILD_DIR)/%.s.o: %.s $(AS)
	$(call echo,Assembling $<,optional) mkdir -p $(dir $@)
	$(muffle)$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(MWCCPSP) $(MWCCGAP_APP) $(AS) | $(VENV_DIR)
	$(call echo,Compiling $<,optional) mkdir -p $(dir $@)
	$(muffle)$(SOTNSTR_APP) process -p -f $< | $(PYTHON) $(MWCCGAP_APP) $@ --src-dir $(dir $<) $(COMPILER_ARGS)
$(BUILD_DIR)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	$(call echo,Building $@,optional) mkdir -p $(dir $@)
	$(muffle)$(LD) -r -b binary -o $@ $<

# Step 2/5 of build
$(foreach target,$(filter-out main,$(GAME)),$(BUILD_DIR)/$(target).elf): $(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.ld $$(call list_files,%)
	$(call link,$*,$@)
$(BUILD_DIR)/st%.elf: $(BUILD_DIR)/st%.ld $$(call list_files,%)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $(BUILD_DIR)/bo%.ld $$(call list_files,%)
	$(call link,st$*,$@)
# All servant files are merged
$(BUILD_DIR)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call list_files,tt_%)
	$(call link,tt_$*,$@)

# Step 3/5 of build
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/$$(call add_ovl_prefix,%).elf
	$(call echo,Building $(notdir $@),optional)
	$(muffle)$(OBJCOPY) -O binary $< $@

# Step 4/5 of build
$(call get_targets): %: $(BUILD_DIR)/%.bin
	$(call echo,Finished building $*)

# Step 5/5 of build
build_pspeu: $(call get_targets)

PHONY_TARGETS += extract_pspeu build_pspeu $(call get_targets)
MUFFLED_TARGETS += $(foreach target,$(filter-out main,$(GAME)),$(BUILD_DIR)/$(target).elf)
