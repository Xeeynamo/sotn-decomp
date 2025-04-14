AS              := $(ALLEGREX)
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -DSOTN_STR -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
LD_FLAGS		:= --gc-sections
CCPSP           := MWCIncludes=$(BIN_DIR) $(WIBO) $(MWCCPSP)
OPT_HI_LIST		:= $(addsuffix .c.o, 80 3250 33F0 A710 C0B0 E6A8 186E8 26948 61F30 624DC 628AC 62FE0 63C90 64EE0 collider)# These objects will get -O4,p instead of -Op
OPT_LEVEL		 = $(if $(filter $(notdir $@),$(OPT_HI_LIST)),-O4$(comma)p,-Op)
COMPILER_ARGS	 = --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --target-encoding sjis --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPT_LEVEL) -opt nointrinsics
AUTO_MERGE_FILES	:= e_init.c

# Step 1/2 of extract
$(BUILD_DIR)/%.ld: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt | $(EXTRACTED_DISK_DIR) $(VENV_DIR)
	$(muffle)$(SPLAT) $<

# Step 2/2 of extract
extract_assets: $(SOTNASSETS)
	cd tools/sotn-assets; $(GO) install
	$(SOTNASSETS) extract config/assets.$(VERSION).yaml
build_assets: $(SOTNASSETS)
	$(SOTNASSETS) build config/assets.$(VERSION).yaml
extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,prefixed)))
	make extract_assets
	make build_assets

# Step 1/5 of build
$(BUILD_DIR)/%.s.o: %.s $(AS)
	$(muffle)mkdir -p $(dir $@)
	$(if $(VERBOSE),,@echo "Assembling $<";) $(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(MWCCPSP) $(MWCCGAP_APP) $(AS) | $(VENV_DIR)/bin
	$(muffle)mkdir -p $(dir $@)
	$(if $(VERBOSE),,@echo "Compiling $<";) $(SOTNSTR_APP) process -p -f $< | $(PYTHON) $(MWCCGAP_APP) $@ --src-dir $(dir $<) $(COMPILER_ARGS)
$(BUILD_DIR)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	$(muffle)mkdir -p $(dir $@)
	$(if $(VERBOSE),,@echo "Building $<";) $(LD) -r -b binary -o $@ $<

# Step 2/5 of build
$(foreach target,$(GAME),$(BUILD_DIR)/$(target).elf): $(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.ld $$(call get_psp_o_files,%)
	$(call link,$*,$@)
$(BUILD_DIR)/st%.elf: $(BUILD_DIR)/st%.ld $$(call get_psp_o_files,%,st)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $(BUILD_DIR)/bo%.ld $$(call get_psp_o_files,%,bo)
	$(call link,st$*,$@)
# All servant files are merged
$(BUILD_DIR)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call get_o_files,servant/tt_%) $(BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link,tt_$*,$@)

# Step 3/5 of build
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/$$(call add_ovl_prefix,%).elf
	$(if $(VERBOSE),,@echo "Stripping $<";) $(OBJCOPY) -O binary $< $@

# Step 4/5 of build
$(call get_targets): %: $(BUILD_DIR)/%.bin

# Step 5/5 of build
build_pspeu: $(call get_targets)

.PHONY: extract_pspeu $(call get_targets) build_pspeu
