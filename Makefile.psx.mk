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

WEAPON0_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f0_$(num).bin $(BUILD_DIR)/weapon/w0_$(num).bin)
WEAPON1_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f1_$(num).bin $(BUILD_DIR)/weapon/w1_$(num).bin)
WEAPON_DIRS   := $(addprefix $(BUILD_DIR)/, weapon $(SRC_DIR)/weapon $(ASM_DIR)/weapon/data $(ASSETS_DIR)/weapon)

MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py
MASPSX          := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.34
MASPSX_21       := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.21

$(WEAPON_DIRS):
	@mkdir -p $@

$(MASPSX_APP):
	git submodule update --init $(MASPSX_DIR)

.PHONY: extract_%
$(addprefix extract_, us hd): $(SOTNASSETS) $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,st,bo)))
	$(call if_version us,$(PNG2S) bdecode $(CONFIG_DIR)/gfx.game.json $(EXTRACTED_DISK_DIR) $(ASSETS_DIR)/game)
	cd $(TOOLS_DIR)/sotn-assets; $(GO) install
	$(SOTNASSETS) extract $(CONFIG_DIR)/assets.$(VERSION).yaml
	$(SOTNASSETS) build $(CONFIG_DIR)/assets.$(VERSION).yaml

build_us build_hd: $(call get_targets)

# todo: these should have an explicit dependency on extract disk
DRA_SYMBOLS := $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt
STMAD_SYMBOLS := $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt
WEAPON_SYMBOLS := $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
STAGE_SYMBOLS := $(if $$(filter mad,%),$(STMAD_SYMBOLS),$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt)
$(BUILD_DIR)/%.ld: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(if $(filter dra,%),$(DRA_SYMBOLS),$(if $(filter weapon,%),$(WEAPON_SYMBOLS))) $(if $(filter weapon,%),,| %_dirs)
	$(SPLAT) $<
	touch $@

# todo: these should have an explicit dependency on extract disk
US_GFXSTAGE_ARGS_ST = $(EXTRACTED_DISK_DIR)/ST/$(call to_upper,$*)/F_$(call to_upper,$*).BIN $(ASSETS_DIR)/st/$*
US_GFXSTAGE_ARGS_BO = $(EXTRACTED_DISK_DIR)/BOSS/$(call to_upper,$*)/F_$(call to_upper,$*).BIN $(ASSETS_DIR)/boss/$*
HD_GFXSTAGE_ARGS_ST = $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/st/$*
HD_GFXSTAGE_ARGS_BO = $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/boss/$*
$(BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(STAGE_SYMBOLS) | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $($(call to_upper,$(VERSION))_GFXSTAGE_ARGS_ST)

$(BUILD_DIR)/bo%.ld: $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).bo%.txt | bo%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $($(call to_upper,$(VERSION))_GFXSTAGE_ARGS_BO)


# We only want this to consider game category overlays, not including main
$(addprefix $(BUILD_DIR)/,$(addsuffix .elf, $(filter-out main,$(GAME)))): $(BUILD_DIR)/%.elf: $$(call list_o_files,%)
	$(call link,$*,$@)

# Main has different prequisites
$(BUILD_DIR)/main.elf: $(BUILD_DIR)/%.elf: $(MAIN_O_FILES) $(BUILD_DIR)/%.ld $(CONFIG_DIR)/undefined_syms.$(VERSION).txt $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).%.txt
	$(call link,$*,$@)

# Need to figure out a structure for link to support this
$(BUILD_DIR)/weapon/%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/$$(subst 0_,_,$(subst 1_,_,%)).c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/$$(subst 0_,_,$(subst 1_,_,%)).data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/$$(subst 0_,_,$(subst 1_,_,%)).sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/$*.map \
		-T $(firstword $(subst _, ,$(subst w,weapon,$*))).ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^

$(BUILD_DIR)/weapon/f0_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o | weapon_dirs
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/weapon/f1_%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f_%.o
	$(LD) -r -b binary -o $@ $<

$(BUILD_DIR)/tt_%.elf: $$(call list_o_files,servant/tt_$$*) | tt_%_dirs
	$(call link,tt_$*,$@)

$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/%,_st) $$(call list_o_files,st,_shared)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $$(call list_o_files,boss/$$*,_st) $$(call list_o_files,boss,_shared)
	$(call link,bo$*,$@)
	


$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.animset.o: $(ASSETS_DIR)/weapon/%.animset.json
	$(TOOLS_DIR)/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*.animset.s -s g_Animset$(subst 1,,$(lastword $(subst _, ,$*)))
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*.animset.s

# assembly and c files
$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@); $(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: %.c $(MASPSX_APP) $(CC1PSX) $(if $(filter src/st/sel/,$(dir %)),src/st/sel/sel.h | stsel_dirs)
	mkdir -p $(dir $@); $(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o: $(SRC_DIR)/weapon/w_%.c $(MASPSX_APP) $(CC1PSX) | weapon_dirs
	$(CPP) $(CPP_FLAGS) -lang-c -DW_$* $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) $(if $(findstring 029,$*),-O1) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

# Only difference for this is MASPSX_21 instead of MASPSX
$(BUILD_DIR)/$(SRC_DIR)/main/psxsdk/libgpu/sys.c.o: $(SRC_DIR)/main/psxsdk/libgpu/sys.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX_21) | $(AS) $(AS_FLAGS) -o $@


.PHONY: $(call get_targets)
main: $(BUILD_DIR)/main.exe
dra ric sel: %: $(BUILD_DIR)/$$(call to_upper,%).BIN
weapon: $(WEAPON_DIRS) $(BUILD_DIR)/WEAPON0.BIN
$(filter-out sel,$(STAGES)): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
$(BOSSES): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
tt_00%: $(BUILD_DIR)/TT_00%.BIN

$(addprefix $(BUILD_DIR)/%,.BIN .bin _raw.bin .exe): $(BUILD_DIR)/$$(call get_filename,%,st,bo).elf
	$(OBJCOPY) -O binary $< $@
$(addprefix $(BUILD_DIR)/,F_%.BIN f_%.bin):
	$(GFXSTAGE) e $(ASSETS_DIR)/$(call get_filename,$*,st/,boss/) $@
$(BUILD_DIR)/WEAPON0.BIN: $(WEAPON0_FILES)
	cat $^ > $@
$(BUILD_DIR)/weapon/%.bin: $(BUILD_DIR)/weapon/%.elf
	$(OBJCOPY) -O binary $< $@
	$(if $(findstring w0, $*),dd status=none if=/dev/zero of=$@ bs=1 seek=12287 count=1 conv=notrunc)
$(BUILD_DIR)/TT_%.BIN: $(BUILD_DIR)/tt_%_raw.bin
	cp $< $@.tmp && truncate -c -s 40960 $@.tmp && mv $@.tmp $@

# Can this be used as the mad target and make the current mad a prerequisite?
mad_fix: $$(call list_o_files,st/mad) $$(call list_o_files,st_) | stmad_dirs
	$(call link,stmad_fix,$@)
	$(OBJCOPY) -O binary $(BUILD_DIR)/stmad_fix.elf $(BUILD_DIR)/MAD.BIN

# Still needs cleanup
.PHONY: %_dirs
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
tt_%_dirs:
	$(foreach dir,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
bo%_dirs:
	$(foreach dir,$(ASM_DIR)/boss/$* $(ASM_DIR)/boss/$*/data $(ASM_DIR)/boss/$*/handwritten $(SRC_DIR)/boss/$* $(ASSETS_DIR)/boss/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
st%_dirs:
	$(foreach dir,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(ASM_DIR)/st/$*/handwritten $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(ASM_DIR)/weapon/data/w_%.data.s: # create a fake empty file if all the data has been imported
	touch $@
$(ASM_DIR)/weapon/data/w_%.sbss.s: # create a fake empty file if all the bss section has been imported
	touch $@



# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	$(PYTHON) $(TOOLS_DIR)/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.json.o: $(ASSETS_DIR)/dra/%.json
	$(PYTHON) $(TOOLS_DIR)/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.json.o: $(ASSETS_DIR)/ric/%.json
	$(PYTHON) $(TOOLS_DIR)/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	mkdir -p $(dir $@)
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.gfxbin.o: $(ASSETS_DIR)/%.gfxbin
	mkdir -p $(dir $@)
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.palbin.o: $(ASSETS_DIR)/%.palbin
	mkdir -p $(dir $@)
	$(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
# dra is the only folder for .dec and for now they are ignored
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.dec.o: $(ASSETS_DIR)/dra/%.dec
	touch $@
# For now ric png.o files are ignored
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.png.o: $(ASSETS_DIR)/ric/%.png
	touch $@
# anything from MAD is an exception and it should be ignored
$(BUILD_DIR)/$(ASSETS_DIR)/st/mad/%.o:
	touch $@

$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o: $(ASSETS_DIR)/weapon/%.png
	$(PYTHON) $(TOOLS_DIR)/png2bin.py $< $@

$(BUILD_DIR)/$(ASSETS_DIR)/%.png.o: $(ASSETS_DIR)/%.png
	mkdir -p $(dir $@)
	$(PNG2S) encode $< \
		$(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s g_saveIcon$(lastword $(subst _, ,$*)) \
		$(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s g_saveIconPal$(lastword $(subst _, ,$*))
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s
	rm $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s
	rm $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s
