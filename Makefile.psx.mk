# configuration
PSX_OVLS		:= dra ric weapon
PSX_KSTAGES		:= cen dre mad no3 np3 nz0 sel st0 wrp
PSX_RSTAGES		:= rwrp
PSX_ALLSTAGES	:= $(addprefix st,$(PSX_KSTAGES)) $(addprefix st,$(PSX_RSTAGES))
PSX_SERVANTS	:= tt_000
PSX_US_TARGETS	:= main $(PSX_OVLS) $(PSX_ALLSTAGES) $(PSX_SERVANTS)
PSX_HD_TARGETS	:= dra tt_000

# immovable
PSX_BASE_SYMS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

extract_us: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSX_US_TARGETS)))
	$(PNG2S) bdecode config/gfx.game.json disks/us assets/game
	make extract_assets
	make build_assets
extract_hd: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSX_HD_TARGETS)))

extract_disk_us: extract_disk_psxus
extract_disk_hd: extract_disk_pspeu
extract_disk_psx%: $(SOTNDISK)
	$(SOTNDISK) extract disks/sotn.$*.cue disks/$*

# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/main.ld: $(CONFIG_DIR)/splat.$(VERSION).main.yaml | main_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/dra.ld: $(CONFIG_DIR)/splat.$(VERSION).dra.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).dra.txt | dra_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/ric.ld: $(CONFIG_DIR)/splat.$(VERSION).ric.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).ric.txt | ric_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/stmad.ld: $(CONFIG_DIR)/splat.$(VERSION).stmad.yaml $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt | stmad_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/$(VERSION)/ST/MAD/F_MAD.BIN $(ASSETS_DIR)/st/mad
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/$(VERSION)/ST/$$(echo '$*' | tr '[:lower:]' '[:upper:]')/F_$$(echo '$*' | tr '[:lower:]' '[:upper:]').BIN $(ASSETS_DIR)/st/$*
$(BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).tt_%.txt | tt_%_dirs
	$(SPLAT) $<
	touch $@
$(BUILD_DIR)/weapon.ld: $(CONFIG_DIR)/splat.$(VERSION).weapon.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
	$(SPLAT) $<
	touch $@

extract_assets: $(SOTNASSETS)
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/CEN/CEN.BIN -o assets/st/cen_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/DRE/DRE.BIN -o assets/st/dre_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/NO3/NO3.BIN -o assets/st/no3_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/NP3/NP3.BIN -o assets/st/np3_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/NZ0/NZ0.BIN -o assets/st/nz0_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/ST0/ST0.BIN -o assets/st/st0_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/WRP/WRP.BIN -o assets/st/wrp_test
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/RWRP/RWRP.BIN -o assets/st/rwrp_test
build_assets: $(SOTNASSETS)
	$(SOTNASSETS) build_all -i assets/st/nz0_test -o src/st/nz0/
	$(SOTNASSETS) build_all -i assets/st/wrp_test -o src/st/wrp/

$(BUILD_DIR)/assets/dra/memcard_%.png.o: assets/dra/memcard_%.png
	mkdir -p $(dir $@)
	$(PNG2S) encode $< \
		$(BUILD_DIR)/assets/dra/memcard_$*.png.s g_saveIcon$* \
		$(BUILD_DIR)/assets/dra/memcard_$*.pal.s g_saveIconPal$*
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/assets/dra/memcard_$*.png.o $(BUILD_DIR)/assets/dra/memcard_$*.png.s
	rm $(BUILD_DIR)/assets/dra/memcard_$*.png.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/assets/dra/memcard_$*.pal.o $(BUILD_DIR)/assets/dra/memcard_$*.pal.s
	rm $(BUILD_DIR)/assets/dra/memcard_$*.pal.s
$(BUILD_DIR)/assets/st/sel/memcard_%.png.o: assets/st/sel/memcard_%.png
	mkdir -p $(dir $@)
	$(PNG2S) encode $< \
		$(BUILD_DIR)/assets/st/sel/memcard_$*.png.s g_saveIcon$* \
		$(BUILD_DIR)/assets/st/sel/memcard_$*.pal.s g_saveIconPal$*
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/assets/st/sel/memcard_$*.png.o $(BUILD_DIR)/assets/st/sel/memcard_$*.png.s
	rm $(BUILD_DIR)/assets/st/sel/memcard_$*.png.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/assets/st/sel/memcard_$*.pal.o $(BUILD_DIR)/assets/st/sel/memcard_$*.pal.s
	rm $(BUILD_DIR)/assets/st/sel/memcard_$*.pal.s
