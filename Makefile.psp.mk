# PSP specific targets
build_pspeu: $(addsuffix _psp,$(PSP_EU_EXTRACT_TARGETS))

extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSP_EU_EXTRACT_TARGETS)))

$(WIBO):
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check $(WIBO).sha256
	chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) $(BIN_DIR)/mwccpsp_219

$(MWCCGAP_APP):
	git submodule init $(MWCCGAP_DIR)
	git submodule update $(MWCCGAP_DIR)

dra_psp: $(BUILD_DIR)/dra.bin
stlib_psp: $(BUILD_DIR)/lib.bin
tt_000_psp: $(BUILD_DIR)/tt_000.bin
stst0_psp: $(BUILD_DIR)/st0.bin
stwrp_psp: $(BUILD_DIR)/wrp.bin
stno4_psp: $(BUILD_DIR)/no4.bin

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/lib.bin: $(BUILD_DIR)/stlib.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/st0.bin: $(BUILD_DIR)/stst0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/wrp.bin: $(BUILD_DIR)/stwrp.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/no4.bin: $(BUILD_DIR)/stno4.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/dra.ld: $(CONFIG_DIR)/splat.pspeu.dra.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.pspeu.dra.txt
	$(SPLAT) $<
$(BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.pspeu.st%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.pspeu.st%.txt
	$(SPLAT) $<
$(BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.pspeu.tt_%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.pspeu.tt_%.txt
	$(SPLAT) $<

$(BUILD_DIR)/dra.elf: $(BUILD_DIR)/dra.ld $(addprefix $(BUILD_DIR)/src/dra/,$(addsuffix .c.o,$(ST_DRA_MERGE))) $$(call list_o_files_psp,dra_psp)
	$(call link_with_deadstrip,dra,$@)
$(BUILD_DIR)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call list_o_files_psp,servant/tt_$$*) $(BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link_with_deadstrip,tt_$*,$@)

$(BUILD_DIR)/stlib.elf: $(BUILD_DIR)/stlib.ld $(addprefix $(BUILD_DIR)/src/st/lib/,$(addsuffix .c.o,$(ST_LIB_MERGE))) $$(call list_o_files_psp,st/lib_psp) $(BUILD_DIR)/assets/st/lib/mwo_header.bin.o
	$(call link_with_deadstrip,stlib,$@)
$(BUILD_DIR)/stst0.elf: $(BUILD_DIR)/stst0.ld $(addprefix $(BUILD_DIR)/src/st/st0/,$(addsuffix .c.o,$(ST_ST0_MERGE))) $$(call list_o_files_psp,st/st0_psp) $(BUILD_DIR)/assets/st/st0/mwo_header.bin.o
	$(call link_with_deadstrip,stst0,$@)
$(BUILD_DIR)/stwrp.elf: $(BUILD_DIR)/stwrp.ld $(addprefix $(BUILD_DIR)/src/st/wrp/,$(addsuffix .c.o,$(ST_WRP_MERGE))) $$(call list_o_files_psp,st/wrp_psp) $(BUILD_DIR)/assets/st/wrp/mwo_header.bin.o
	$(call link_with_deadstrip,stwrp,$@)
$(BUILD_DIR)/stno4.elf: $(BUILD_DIR)/stno4.ld $(addprefix $(BUILD_DIR)/src/st/no4/,$(addsuffix .c.o,$(ST_NO4_MERGE))) $$(call list_o_files_psp,st/no4_psp) $(BUILD_DIR)/assets/st/no4/mwo_header.bin.o
	$(call link_with_deadstrip,stno4,$@)

# Recipes
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: %.c $(MWCCPSP) $(MWCCGAP_APP)
	@mkdir -p $(dir $@)
	$(MWCCGAP) $< $@ --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPTIMIZATION)

$(BUILD_DIR)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<
