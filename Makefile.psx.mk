# Game OVL options: main dra ric weapon
# Both stage and reverse stage fall under "STAGES" variable, they are split only for readability.
# Stage OVL options: are cat cen chi dai dre lib mad no0 no1 no2 no3 no4 np3 nz0 nz1 sel st0 top wrp
# Reverse stage OVL options: rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp
# Boss OVL options: bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8
# Servant OVL options: tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006

ifeq ($(VERSION),us)
GAME		:= main dra ric weapon
STAGES		:= cen chi dre lib mad no0 no1 no3 no4 np3 nz0 sel st0 wrp
STAGES   	+= rwrp
BOSSES		:= bo4 mar rbo3
SERVANTS	:= tt_000 tt_001 tt_002 tt_003 tt_004
else ifeq ($(VERSION),hd)
GAME		:= dra ric
STAGES		:= cen wrp
STAGES		+= 
BOSSES		:= 
SERVANTS	:= tt_000
endif

# compiler
CC1PSX          := $(BIN_DIR)/cc1-psx-26
CC              := $(CC1PSX)
AS              := $(CROSS)as
CPP             := $(CROSS)cpp

# flags
CC_FLAGS        += -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -g
CPP_FLAGS       += -Iinclude -Iinclude/psxsdk -undef -Wall -fno-builtin
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DNO_LOGS -DHACKS -DUSE_INCLUDE_ASM
CPP_FLAGS       += -D_internal_version_$(VERSION) -DSOTN_STR
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
PSXCC_FLAGS     := -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff
LD_FLAGS        := -nostdlib --no-check-sections

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

$(MASPSX_APP):
	git submodule update --init $(MASPSX_DIR)

.PHONY: extract_%
ifeq ($(VERSION),us)
IF_US_BDECODE := $(PNG2S) bdecode $(CONFIG_DIR)/gfx.game.json $(EXTRACTED_DISK_DIR) $(ASSETS_DIR)/game
endif
$(addprefix extract_, us hd): $(SOTNASSETS) $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,st,bo)))
	$(IF_US_BDECODE)
	cd $(TOOLS_DIR)/sotn-assets; $(GO) install
	$(SOTNASSETS) extract $(CONFIG_DIR)/assets.$(VERSION).yaml
	$(SOTNASSETS) build $(CONFIG_DIR)/assets.$(VERSION).yaml

build_us build_hd: $(call get_targets)

# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/main.ld: $(CONFIG_DIR)/splat.$(VERSION).main.yaml | main_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/dra.ld: $(CONFIG_DIR)/splat.$(VERSION).dra.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).dra.txt | dra_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/ric.ld: $(CONFIG_DIR)/splat.$(VERSION).ric.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).ric.txt | ric_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/stmad.ld: $(CONFIG_DIR)/splat.$(VERSION).stmad.yaml $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt | stmad_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $(EXTRACTED_DISK_DIR)/ST/MAD/F_MAD.BIN $(ASSETS_DIR)/st/mad
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $(EXTRACTED_DISK_DIR)/ST/$$(echo '$*' | tr '[:lower:]' '[:upper:]')/F_$$(echo '$*' | tr '[:lower:]' '[:upper:]').BIN $(ASSETS_DIR)/st/$*
$(BUILD_DIR)/bo%.ld: $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).bo%.txt | bo%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $(EXTRACTED_DISK_DIR)/BOSS/$$(echo '$*' | tr '[:lower:]' '[:upper:]')/F_$$(echo '$*' | tr '[:lower:]' '[:upper:]').BIN $(ASSETS_DIR)/boss/$*
build/hd/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/st/$*
$(BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).tt_%.txt | tt_%_dirs
	$(SPLAT) $<
	touch $@
$(BUILD_DIR)/weapon.ld: $(CONFIG_DIR)/splat.$(VERSION).weapon.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
	$(SPLAT) $<
	touch $@

$(BUILD_DIR)/dra.elf: $(call list_o_files,dra)
	echo $(call list_o_files,dra)
	$(call link,dra,$@)
$(BUILD_DIR)/tt_%.elf: $$(call list_o_files,servant/tt_$$*) | tt_%_dirs
	$(call link,tt_$*,$@)

$(BUILD_DIR)/src/st/sel/%.c.o: src/st/sel/%.c $(MASPSX_APP) $(CC1PSX) src/st/sel/sel.h | stsel_dirs
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%_1.animset.o: $(ASSETS_DIR)/weapon/%_1.animset.json
	$(TOOLS_DIR)/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_1.animset.s -s g_Animset
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_1.animset.s
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%_2.animset.o: $(ASSETS_DIR)/weapon/%_2.animset.json
	$(TOOLS_DIR)/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*_2.animset.s -s g_Animset2
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

# anything from MAD is an exception and it should be ignored
$(BUILD_DIR)/$(ASSETS_DIR)/st/mad/%.o:
	touch $@

.PHONY: main
main: $(MAIN_TARGET).exe
.PHONY: %_dirs
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(MAIN_TARGET).exe: $(MAIN_TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(MAIN_TARGET).elf: $(MAIN_O_FILES) $(BUILD_DIR)/main.ld $(CONFIG_DIR)/undefined_syms.$(VERSION).txt $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).main.txt
	$(LD) $(LD_FLAGS) -o $@ \
	-Map $(MAIN_TARGET).map \
	-T $(BUILD_DIR)/main.ld \
	-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).main.txt
###

.PHONY: $(call get_targets)
dra ric sel: %: $(BUILD_DIR)/$$(call to_upper,%).BIN
$(filter-out sel,$(STAGES)): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
$(BOSSES): %: $(BUILD_DIR)/$(call to_upper,%).BIN $(BUILD_DIR)/F_$(call to_upper,%).BIN

$(BUILD_DIR)/ric.elf: $(call list_o_files,ric)
	$(call link,ric,$@)
$(addprefix $(BUILD_DIR)/,F_%.BIN f_%.bin):
	$(GFXSTAGE) e $(ASSETS_DIR)/$(call get_filename,$*,st/,boss/) $@
$(addprefix $(BUILD_DIR)/,%.BIN %.bin %_raw.bin): $(BUILD_DIR)/$$(call get_filename,%,st,bo).elf
	$(OBJCOPY) -O binary $< $@

tt_00%: $(BUILD_DIR)/TT_00%.BIN

$(BUILD_DIR)/TT_%.BIN: $(BUILD_DIR)/tt_%_raw.bin
	cp $< $@.tmp
	truncate -c -s 40960 $@.tmp
	mv $@.tmp $@

mad_fix: stmad_dirs $$(call list_o_files,st/mad) $$(call list_o_files,st)
	$(LD) $(LD_FLAGS) -o $(BUILD_DIR)/stmad_fix.elf \
		-Map $(BUILD_DIR)/stmad_fix.map \
		-T $(BUILD_DIR)/stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt
	$(OBJCOPY) -O binary $(BUILD_DIR)/stmad_fix.elf $(BUILD_DIR)/MAD.BIN

.PHONY: %_dirs
tt_%_dirs:
	$(foreach dir,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
bo%_dirs:
	$(foreach dir,$(ASM_DIR)/boss/$* $(ASM_DIR)/boss/$*/data $(ASM_DIR)/boss/$*/handwritten $(SRC_DIR)/boss/$* $(ASSETS_DIR)/boss/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
st%_dirs:
	$(foreach dir,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(ASM_DIR)/st/$*/handwritten $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/stmad.elf: $$(call list_o_files,st/mad) $$(call list_o_files,st,_shared)
	$(LD) $(LD_FLAGS) -o $@ \
		-Map $(BUILD_DIR)/stmad.map \
		-T $(BUILD_DIR)/stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.beta.txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt
$(BUILD_DIR)/stsel.elf: $$(call list_o_files,st/sel) $$(call list_o_files,st,_shared)
	$(call link,stsel,$@)

$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/$$*,_st) $$(call list_o_files,st,_shared)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $$(call list_o_files,boss/$$*,_st) $$(call list_o_files,boss,_shared)
	$(call link,bo$*,$@)

# Weapon overlays
WEAPON0_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f0_$(num).bin $(BUILD_DIR)/weapon/w0_$(num).bin)
WEAPON1_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f1_$(num).bin $(BUILD_DIR)/weapon/w1_$(num).bin)
WEAPON_DIRS   := $(BUILD_DIR)/$(ASSETS_DIR)/weapon $(BUILD_DIR)/$(ASM_DIR)/weapon/data $(BUILD_DIR)/$(SRC_DIR)/weapon $(BUILD_DIR)/weapon

.PHONY: weapon
weapon: $(WEAPON_DIRS) $(BUILD_DIR)/WEAPON0.BIN
$(WEAPON_DIRS):
	@mkdir -p $@
$(BUILD_DIR)/WEAPON0.BIN: $(WEAPON0_FILES)
	cat $^ > $@
$(BUILD_DIR)/weapon/f%.bin: $(BUILD_DIR)/weapon/f%.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/weapon/w%.bin: $(BUILD_DIR)/weapon/w%.elf
	$(OBJCOPY) -O binary $< $@
	dd status=none if=/dev/zero of=$@ bs=1 seek=12287 count=1 conv=notrunc
$(ASM_DIR)/weapon/data/w_%.data.s: # create a fake empty file if all the data has been imported
	touch $@
$(ASM_DIR)/weapon/data/w_%.sbss.s: # create a fake empty file if all the bss section has been imported
	touch $@
$(BUILD_DIR)/weapon/w0_%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/w0_$*.map \
		-T weapon0.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
$(BUILD_DIR)/weapon/w1_%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/w_%.sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/w1_$*.map \
		-T weapon1.ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o: $(SRC_DIR)/weapon/w_%.c $(MASPSX_APP) $(CC1PSX) | weapon_dirs
	$(CPP) $(CPP_FLAGS) -lang-c -DW_$* $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_029.c.o: $(SRC_DIR)/weapon/w_029.c $(MASPSX_APP) $(CC1PSX) | weapon_dirs
	$(CPP) $(CPP_FLAGS) -lang-c -DW_029 $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) -O1 | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/weapon/f0_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o | weapon_dirs
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/weapon/f1_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o: $(ASSETS_DIR)/weapon/%.png
	$(PYTHON) $(TOOLS_DIR)/png2bin.py $< $@
