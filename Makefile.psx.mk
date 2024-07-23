# flags
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
PSXCC_FLAGS     := -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff

# configuration
PSX_OVLS		:= dra ric weapon
PSX_KSTAGES		:= cen dre mad no3 np3 nz0 sel st0 wrp
PSX_RSTAGES		:= rwrp
PSX_ALLSTAGES	:= $(addprefix st,$(PSX_KSTAGES)) $(addprefix st,$(PSX_RSTAGES))
PSX_SERVANTS	:= tt_000
PSX_US_TARGETS	:= main $(PSX_OVLS) $(PSX_ALLSTAGES) $(PSX_SERVANTS)
PSX_HD_TARGETS	:= dra tt_000 stwrp

# immovable
PSX_BASE_SYMS	:= $(CONFIG_DIR)/symbols.$(VERSION).txt

extract_us: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSX_US_TARGETS)))
	$(PNG2S) bdecode config/gfx.game.json disks/us assets/game
	make extract_assets
	make build_assets
extract_hd: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSX_HD_TARGETS)))
	make extract_assets_hd
	make build_assets

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
build/hd/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/pspeu/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/st/$*
$(BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).tt_%.txt | tt_%_dirs
	$(SPLAT) $<
	touch $@
$(BUILD_DIR)/weapon.ld: $(CONFIG_DIR)/splat.$(VERSION).weapon.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
	$(SPLAT) $<
	touch $@

$(BUILD_DIR)/src/st/sel/%.c.o: src/st/sel/%.c $(MASPSX_APP) $(CC1PSX) src/st/sel/sel.h | stsel_dirs
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%_1.animset.o: $(ASSETS_DIR)/weapon/%_1.animset.json
	./tools/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_1.animset.s -s g_Animset
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_1.animset.s
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%_2.animset.o: $(ASSETS_DIR)/weapon/%_2.animset.json
	./tools/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_2.animset.s -s g_Animset2
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_2.animset.s

# assembly and c files
$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: %.c $(MASPSX_APP) $(CC1PSX)
	mkdir -p $(dir $@)
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

$(BUILD_DIR)/$(SRC_DIR)/main/psxsdk/libgpu/sys.c.o: $(SRC_DIR)/main/psxsdk/libgpu/sys.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX_21) | $(AS) $(AS_FLAGS) -o $@

extract_assets: $(SOTNASSETS)
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/CEN/CEN.BIN -o assets/st/cen
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/DRE/DRE.BIN -o assets/st/dre
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/NO3/NO3.BIN -o assets/st/no3
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/NP3/NP3.BIN -o assets/st/np3
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/NZ0/NZ0.BIN -o assets/st/nz0
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/ST0/ST0.BIN -o assets/st/st0
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/WRP/WRP.BIN -o assets/st/wrp
	$(SOTNASSETS) extract -stage_ovl disks/$(VERSION)/ST/RWRP/RWRP.BIN -o assets/st/rwrp
extract_assets_hd: $(SOTNASSETS)
	$(SOTNASSETS) extract -stage_ovl disks/pspeu/PSP_GAME/USRDIR/res/ps/hdbin/wrp.bin -o assets/st/wrp
build_assets: $(SOTNASSETS)
	$(SOTNASSETS) build_all -i assets/st/cen -o src/st/cen/
	$(SOTNASSETS) build_all -i assets/st/dre -o src/st/dre/
	$(SOTNASSETS) build_all -i assets/st/no3 -o src/st/no3/
	$(SOTNASSETS) build_all -i assets/st/np3 -o src/st/np3/
	$(SOTNASSETS) build_all -i assets/st/nz0 -o src/st/nz0/
	$(SOTNASSETS) build_all -i assets/st/st0 -o src/st/st0/
	$(SOTNASSETS) build_all -i assets/st/wrp -o src/st/wrp/
	$(SOTNASSETS) build_all -i assets/st/rwrp -o src/st/rwrp/

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
