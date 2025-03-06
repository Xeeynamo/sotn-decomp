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
CC_FLAGS        += -G0 -w -O2 $(addprefix -f,unsigned-char peephole function-cse pcc-struct-return common verbose-asm) -msoft-float -g
CPP_FLAGS       += -Iinclude -Iinclude/psxsdk -undef -Wall -fno-builtin
CPP_FLAGS     	+= $(addprefix -D,mips __GNUC__=2 __OPTIMIZE__ __mips__ __mips psx __psx__ __psx _PSYQ __EXTENSIONS__ _MIPSEL)
CPP_FLAGS		+= $(addprefix -D,_LANGUAGE_C LANGUAGE_C NO_LOGS HACKS USE_INCLUDE_ASM _internal_version_$(VERSION) SOTN_STR)
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
PSXCC_FLAGS     := -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff
LD_FLAGS        := -nostdlib --no-check-sections

COMPILER		:= $(CPP) $(CPP_FLAGS) -lang-c
COMPILER_ARGS	:= | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o
COMPILER_REQS	 = $(MASPSX_APP) $(CC1PSX) $(if $(filter src/st/sel/,$(dir %)),src/st/sel/sel.h | stsel_dirs)

# libs
PSXLIBS         := libc libc2 libapi libetc libcard libgpu libgs libgte libcd libsnd libspu

# Files
PSXLIB_DIRS     := $(addprefix psxsdk/,$(slash) $(PSXLIBS))
PSXLIB_DATA_DIRS := $(addprefix data/,$(slash) $(PSXLIB_DIRS))
MAIN_ASM_DIRS   := $(addprefix $(ASM_DIR)/main/,$(slash) $(PSXLIB_DIRS) $(PSXLIB_DATA_DIRS))
MAIN_SRC_DIRS   := $(addprefix $(SRC_DIR)/main/,$(slash) $(PSXLIB_DIRS))

MAIN_S_FILES    := $(wildcard $(addsuffix /*.s, $(MAIN_ASM_DIRS)))
MAIN_C_FILES    := $(wildcard $(addsuffix /*.c, $(MAIN_SRC_DIRS)))
MAIN_O_FILES    := $(patsubst %.s,%.s.o,$(MAIN_S_FILES))
MAIN_O_FILES    += $(patsubst %.c,%.c.o,$(MAIN_C_FILES))
MAIN_O_FILES    := $(addprefix $(BUILD_DIR)/,$(MAIN_O_FILES))

WEAPON0_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f0_$(num).bin $(BUILD_DIR)/weapon/w0_$(num).bin)
WEAPON1_FILES := $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f1_$(num).bin $(BUILD_DIR)/weapon/w1_$(num).bin)
WEAPON_DIRS   := $(addprefix $(BUILD_DIR)/, weapon $(SRC_DIR)/weapon $(ASM_DIR)/weapon/data $(ASSETS_DIR)/weapon)

DRA_SYMBOLS := $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt
STMAD_SYMBOLS := $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt
WEAPON_SYMBOLS := $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
STAGE_SYMBOLS := $(if $$(filter mad,%),$(STMAD_SYMBOLS),$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt)

US_GFXSTAGE_ARGS_ST = $(EXTRACTED_DISK_DIR)/ST/$(call to_upper,$*)/F_$(call to_upper,$*).BIN $(ASSETS_DIR)/st/$*
US_GFXSTAGE_ARGS_BO = $(EXTRACTED_DISK_DIR)/BOSS/$(call to_upper,$*)/F_$(call to_upper,$*).BIN $(ASSETS_DIR)/boss/$*
HD_GFXSTAGE_ARGS_ST = $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/st/$*
HD_GFXSTAGE_ARGS_BO = $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/boss/$*

#/* Start dirs group */
.PHONY: %_dirs
main_dirs:
	mkdir -p $(addprefix $(BUILD_DIR)/,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS))
tt_%_dirs:
	mkdir -p $(addprefix $(BUILD_DIR)/,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*)
bo%_dirs:
	mkdir -p $(addprefix $(BUILD_DIR)/,$(ASM_DIR)/boss/$* $(ASM_DIR)/boss/$*/data $(ASM_DIR)/boss/$*/handwritten $(SRC_DIR)/boss/$* $(ASSETS_DIR)/boss/$*)
st%_dirs:
	mkdir -p $(addprefix $(BUILD_DIR)/,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(ASM_DIR)/st/$*/handwritten $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*)
%_dirs:
	mkdir -p $(addprefix $(BUILD_DIR)/,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*)
$(WEAPON_DIRS):
	mkdir -p $@
#/* End dirs group */

.PHONY: extract_%
# Step 1/2 of extract
# The non-stage/boss .ld targets mostly follow the same pattern, but have slight differences with the prerequisites
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR:pspeu=no)/%.ld: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(if $(filter dra ric,%),$(DRA_SYMBOLS),$(if $(filter weapon,%),$(WEAPON_SYMBOLS))) $(if $(filter weapon,%),,| %_dirs)
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR:pspeu=no)/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(STAGE_SYMBOLS) | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $($(call to_upper,$(VERSION))_GFXSTAGE_ARGS_ST)
$(BUILD_DIR:pspeu=no)/bo%.ld: $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).bo%.txt | bo%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d $($(call to_upper,$(VERSION))_GFXSTAGE_ARGS_BO)

# Step 2/2 of extract
$(addprefix extract_,us hd): $(SOTNASSETS) $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,prefixed)))
	$(call if_version,us,$(PNG2S) bdecode $(CONFIG_DIR)/gfx.game.json $(EXTRACTED_DISK_DIR) $(ASSETS_DIR)/game)
	cd $(TOOLS_DIR)/sotn-assets; $(GO) install
	$(SOTNASSETS) extract $(CONFIG_DIR)/assets.$(VERSION).yaml
	$(SOTNASSETS) build $(CONFIG_DIR)/assets.$(VERSION).yaml

# Step 1/6 of build
$(ASM_DIR)/weapon/data/w_%.s:# Create an empty file if all the data or bss has been imported
	touch $@

# Step 2/6 of build
$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@); $(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(COMPILER_REQS)
	mkdir -p $(dir $@); $(COMPILER) $< $(call if_version,pspeu,$@) $(COMPILER_ARGS) $(call if_version,us hd,$@)
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o: $(SRC_DIR)/weapon/w_%.c $(MASPSX_APP) $(CC1PSX) | weapon_dirs
	$(CPP) $(CPP_FLAGS) -lang-c -DW_$* $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) $(if $(findstring 029,$*),-O1) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@
# Only difference for this is MASPSX_21 instead of MASPSX
$(BUILD_DIR)/$(SRC_DIR)/main/psxsdk/libgpu/sys.c.o: $(SRC_DIR)/main/psxsdk/libgpu/sys.c $(MASPSX_APP) $(CC1PSX)
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX_21) | $(AS) $(AS_FLAGS) -o $@

# Step 3/6 of build
# Main has different prequisites
$(BUILD_DIR)/main.elf: $(BUILD_DIR)/%.elf: $(MAIN_O_FILES) $(BUILD_DIR)/%.ld $(CONFIG_DIR)/undefined_syms.$(VERSION).txt $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).%.txt
	$(call link,$*,$@)
# We only want this to consider game category overlays, not including main
$(addprefix $(BUILD_DIR:pspeu=no)/,$(addsuffix .elf,$(filter-out main,$(GAME)))): $(BUILD_DIR)/%.elf: $$(call list_o_files,%)
	$(call link,$*,$@)
# Ideally, this would use link as well, but it's probably too different for that to make sense.
# The .ld is not currently autogenerated.
$(BUILD_DIR)/weapon/%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/$$(subst 0_,_,$(subst 1_,_,%)).c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/$$(subst 0_,_,$(subst 1_,_,%)).data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/$$(subst 0_,_,$(subst 1_,_,%)).sbss.s.o
	$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/$*.map \
		-T $(firstword $(subst _, ,$(subst w,weapon,$*))).ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^
# These two can probably be combined
$(BUILD_DIR)/weapon/f%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f$$(subst 0_,_,$(subst 1_,_,%)).o | weapon_dirs
	$(LD) -r -b binary -o $@ $<
$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/%,_st) $$(call list_o_files,st,_shared)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $$(call list_o_files,boss/$$*,_st) $$(call list_o_files,boss,_shared)
	$(call link,bo$*,$@)
$(BUILD_DIR)/tt_%.elf: $$(call list_o_files,servant/tt_$$*) | tt_%_dirs
	$(call link,tt_$*,$@)

# Step 4/6 of build
$(addprefix $(BUILD_DIR)/%,.BIN .bin _raw.bin .exe): $(BUILD_DIR)/$$(call get_filename,%,st,bo).elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/WEAPON0.BIN: $(WEAPON0_FILES)
	cat $^ > $@
$(BUILD_DIR)/weapon/%.bin: $(BUILD_DIR)/weapon/%.elf
	$(OBJCOPY) -O binary $< $@
	$(if $(findstring w0, $*),dd status=none if=/dev/zero of=$@ bs=1 seek=12287 count=1 conv=notrunc)
$(addprefix $(BUILD_DIR:pspeu=no)/,F_%.BIN f_%.bin):
	$(GFXSTAGE) e $(ASSETS_DIR)/$(call get_filename,$*,st/,boss/) $@
$(BUILD_DIR)/TT_%.BIN: $(BUILD_DIR)/tt_%_raw.bin
	cp $< $@.tmp && truncate -c -s 40960 $@.tmp && mv $@.tmp $@

# Step 5/6 of build
.PHONY: $(call get_targets)
main: $(BUILD_DIR)/main.exe
dra ric sel: %: $(BUILD_DIR)/$$(call to_upper,%).BIN
weapon: $(WEAPON_DIRS) $(BUILD_DIR)/WEAPON0.BIN
$(filter-out sel,$(STAGES)): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
$(BOSSES): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
tt_00%: $(BUILD_DIR)/TT_00%.BIN

# Step 6/6 of build
build_us build_hd: $(call get_targets)

# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.json.o: $(ASSETS_DIR)/%.json
	$(PYTHON) $(TOOLS_DIR)/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	$(PYTHON) $(TOOLS_DIR)/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s

$(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	mkdir -p $(dir $@); $(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.gfxbin.o: $(ASSETS_DIR)/%.gfxbin
	mkdir -p $(dir $@); $(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.palbin.o: $(ASSETS_DIR)/%.palbin
	mkdir -p $(dir $@); $(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<

$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o: $(ASSETS_DIR)/weapon/%.png
	$(PYTHON) $(TOOLS_DIR)/png2bin.py $< $@
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.animset.o: $(ASSETS_DIR)/weapon/%.animset.json
	$(TOOLS_DIR)/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*.animset.s -s g_Animset$(subst 1,,$(lastword $(subst _, ,$*)))
	$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*.animset.s

$(BUILD_DIR)/$(ASSETS_DIR)/%.png.o: $(ASSETS_DIR)/%.png
	mkdir -p $(dir $@)
	$(PNG2S) encode $< \
		$(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s g_saveIcon$(lastword $(subst _, ,$*)) \
		$(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s g_saveIconPal$(lastword $(subst _, ,$*))
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s
	rm $(addprefix $(BUILD_DIR)/$(ASSETS_DIR)/,$*.png.s $*.pal.s)

# dra is the only folder for .dec and for now they are ignored
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.dec.o: $(ASSETS_DIR)/dra/%.dec
	touch $@
# For now ric png.o files are ignored
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.png.o: $(ASSETS_DIR)/ric/%.png
	touch $@
# anything from MAD is an exception and it should be ignored
$(BUILD_DIR)/$(ASSETS_DIR)/st/mad/%.o:
	touch $@
