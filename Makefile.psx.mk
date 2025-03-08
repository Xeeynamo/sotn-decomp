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
BOSSES		:= bo4 mar rbo3 rbo5
SERVANTS	:= tt_000 tt_001 tt_002 tt_003 tt_004
else ifeq ($(VERSION),hd)
GAME		:= dra ric
STAGES		:= cen wrp
STAGES		+= 
BOSSES		:= 
SERVANTS	:= tt_000
endif

# Compiler
CC1PSX          := $(BIN_DIR)/cc1-psx-26
CC              := $(CC1PSX)
AS              := $(CROSS)as
CPP             := $(CROSS)cpp
MASPSX			 = $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=$(if $(findstring libgpu/sys.c.o,$@),2.21,2.34)

# Flags
CC_FLAGS        += -G0 -w -O2 $(addprefix -f,unsigned-char peephole function-cse pcc-struct-return common verbose-asm) -msoft-float -g
CPP_FLAGS       += -Iinclude -Iinclude/psxsdk -undef -Wall -fno-builtin
CPP_FLAGS     	+= $(addprefix -D,mips __GNUC__=2 __OPTIMIZE__ __mips__ __mips psx __psx__ __psx _PSYQ __EXTENSIONS__ _MIPSEL)
CPP_FLAGS		+= $(addprefix -D,_LANGUAGE_C LANGUAGE_C NO_LOGS HACKS USE_INCLUDE_ASM _internal_version_$(VERSION) SOTN_STR)
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
PSXCC_FLAGS     := -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff
LD_FLAGS        := -nostdlib --no-check-sections

COMPILER		:= $(CPP) $(CPP_FLAGS) -lang-c
COMPILER_ARGS	 = | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) $(if $(findstring 029,$*),-O1) | $(MASPSX) | $(AS) $(AS_FLAGS) -o
COMPILER_REQS	 = $(MASPSX_APP) $(CC1PSX) $(if $(filter src/st/sel/,$(dir %)),src/st/sel/sel.h | stsel-dirs)

# Libs
PSXLIBS         := libc libc2 libapi libetc libcard libgpu libgs libgte libcd libsnd libspu

# Dirs
PSXLIB_DIRS     := $(addprefix psxsdk/,$(slash) $(PSXLIBS))
PSXLIB_DATA_DIRS := $(addprefix data/,$(slash) $(PSXLIB_DIRS))
MAIN_ASM_DIRS   := $(subst //,/,$(addprefix $(ASM_DIR)/main/,$(slash) $(PSXLIB_DIRS) $(PSXLIB_DATA_DIRS)))
MAIN_SRC_DIRS   := $(subst //,/,$(addprefix $(SRC_DIR)/main/,$(slash) $(PSXLIB_DIRS)))

# Files
MAIN_S_FILES    := $(subst //,/,$(wildcard $(addsuffix /*.s, $(MAIN_ASM_DIRS))))
MAIN_C_FILES    := $(subst //,/,$(wildcard $(addsuffix /*.c, $(MAIN_SRC_DIRS))))
MAIN_O_FILES    := $(patsubst %.s,%.s.o,$(MAIN_S_FILES))
MAIN_O_FILES    += $(patsubst %.c,%.c.o,$(MAIN_C_FILES))
MAIN_O_FILES    := $(addprefix $(BUILD_DIR)/,$(MAIN_O_FILES))

WEAPON0_FILES 	:= $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f0_$(num).bin $(BUILD_DIR)/weapon/w0_$(num).bin)
WEAPON1_FILES 	:= $(foreach num,$(shell seq -w 000 058),$(BUILD_DIR)/weapon/f1_$(num).bin $(BUILD_DIR)/weapon/w1_$(num).bin)

DRA_SYMBOLS 	:= $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt
STMAD_SYMBOLS 	:= $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt
WEAPON_SYMBOLS 	:= $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
STAGE_SYMBOLS 	:= $(if $$(filter mad,%),$(STMAD_SYMBOLS),$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt)

US_GFXSTAGE_ARGS_ST = $(EXTRACTED_DISK_DIR)/ST/$(call to_upper,$*)/F_$(call to_upper,$*).BIN $(ASSETS_DIR)/st/$*
US_GFXSTAGE_ARGS_BO = $(EXTRACTED_DISK_DIR)/BOSS/$(call to_upper,$*)/F_$(call to_upper,$*).BIN $(ASSETS_DIR)/boss/$*
HD_GFXSTAGE_ARGS_ST = $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/st/$*
HD_GFXSTAGE_ARGS_BO = $(EXTRACTED_DISK_DIR:hd=pspeu)/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/boss/$*

# Todo: Revise these so their logic is a bit more straightforward
main-dirs:
	$(muffle)mkdir -p $(call get_build_dirs,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS))
$(call get_build_dirs,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS)): main-dirs

st%-dirs:
	$(muffle)mkdir -p $(call get_build_dirs,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(ASM_DIR)/st/$*/handwritten $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*)
$(call get_build_dirs,$(ASM_DIR)/st/% $(ASM_DIR)/st/%/data $(ASM_DIR)/st/%/handwritten $(SRC_DIR)/st/% $(ASSETS_DIR)/st/%): st%-dirs

bo%-dirs:
	$(muffle)mkdir -p $(call get_build_dirs,$(ASM_DIR)/boss/$* $(ASM_DIR)/boss/$*/data $(ASM_DIR)/boss/$*/handwritten $(SRC_DIR)/boss/$* $(ASSETS_DIR)/boss/$*)
$(call get_build_dirs,$(ASM_DIR)/boss/% $(ASM_DIR)/boss/%/data $(ASM_DIR)/boss/%/handwritten $(SRC_DIR)/boss/% $(ASSETS_DIR)/boss/%): bo%-dirs

tt_%-dirs:
	$(muffle)mkdir -p $(call get_build_dirs,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*)
$(call get_build_dirs,$(ASM_DIR)/servant/tt_% $(ASM_DIR)/servant/tt_%/data $(SRC_DIR)/servant/tt_% $(ASSETS_DIR)/servant/tt_%): tt_%-dirs

weapon-dirs:
	$(muffle)mkdir -p $(call get_build_dirs, weapon $(SRC_DIR)/weapon $(ASM_DIR)/weapon/data $(ASSETS_DIR)/weapon)
$(call get_build_dirs, weapon $(SRC_DIR)/weapon $(ASM_DIR)/weapon/data $(ASSETS_DIR)/weapon): | weapon-dirs

%-dirs:
	$(muffle)mkdir -p $(call get_build_dirs,$(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*)
$(call get_build_dirs,$(ASM_DIR)/%/data $(SRC_DIR)/% $(ASSETS_DIR)/%): | %-dirs

# Step 1/2 of extract
# The non-stage/boss .ld targets mostly follow the same pattern, but have slight differences with the prerequisites
$(BUILD_DIR:pspeu=no)/%.ld: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(if $(filter dra ric,%),$(DRA_SYMBOLS),$(if $(filter weapon,%),$(WEAPON_SYMBOLS))) | %-dirs $(EXTRACTED_DISK_DIR)
	$(muffle)$(SPLAT) $<; touch $@
$(BUILD_DIR:pspeu=no)/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(STAGE_SYMBOLS) | st%-dirs $(EXTRACTED_DISK_DIR)
	$(muffle)$(SPLAT) $<
	$(muffle)$(GFXSTAGE) d $($(call to_upper,$(VERSION))_GFXSTAGE_ARGS_ST)
$(BUILD_DIR:pspeu=no)/bo%.ld: $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).bo%.txt | bo%-dirs $(EXTRACTED_DISK_DIR)
	$(muffle)$(SPLAT) $<
	$(muffle)$(GFXSTAGE) d $($(call to_upper,$(VERSION))_GFXSTAGE_ARGS_BO)

# Step 2/2 of extract
$(addprefix extract_,us hd): $(SOTNASSETS) $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,prefixed)))
	$(call echo,Extracting $(VERSION) assets)
	$(call if_version,us,$(PNG2S) bdecode $(CONFIG_DIR)/gfx.game.json $(EXTRACTED_DISK_DIR) $(ASSETS_DIR)/game)
	$(foreach action,extract build,$(SOTNASSETS) $(action) $(CONFIG_DIR)/assets.$(VERSION).yaml;)

# Step 1/6 of build
$(ASM_DIR)/weapon/data/w_%.s:# Create an empty file if all the data or bss has been imported
	$(muffle)$(call echo,Creating empty file: $@,optional) touch $@

# Step 2/6 of build
# Todo: add overlay extraction as an explicit dependency
$(BUILD_DIR)/%.s.o: %.s $(AS) | $$(dir $$@)
	$(muffle)$(call echo,Assembling $<,optional) $(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(COMPILER_REQS)
	$(muffle)$(call echo,Compiling $<,optional) $(COMPILER) $< $(call if_version,pspeu,$@) $(COMPILER_ARGS) $(call if_version,us hd,$@)
$(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o: $(SRC_DIR)/weapon/w_%.c $(COMPILER_REQS)
	$(muffle)$(call echo,Compiling $<,optional) $(COMPILER) -DW_$* $< $(call if_version,pspeu,$@) $(COMPILER_ARGS) $(call if_version,us hd,$@)

# Step 3/6 of build
# Main has different prequisites
$(BUILD_DIR)/main.elf: $(BUILD_DIR)/%.elf: $(MAIN_O_FILES) $(BUILD_DIR)/%.ld $(CONFIG_DIR)/undefined_syms.$(VERSION).txt $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).%.txt
	$(call link,$*,$@)
# We only want this to consider game category overlays, not including main
$(addprefix $(BUILD_DIR:pspeu=no)/,$(addsuffix .elf,$(filter-out main,$(GAME)))): $(BUILD_DIR)/%.elf: $$(call list_o_files,%)
	$(call link,$*,$@)
$(BUILD_DIR)/st%.elf: $$(call list_o_files,st/%,_st) $$(call list_o_files,st,_shared)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $$(call list_o_files,boss/$$*,_st) $$(call list_o_files,boss,_shared)
	$(call link,bo$*,$@)
$(BUILD_DIR)/tt_%.elf: $$(call list_o_files,servant/tt_$$*) | tt_%-dirs
	$(call link,tt_$*,$@)
$(BUILD_DIR)/weapon/f%.elf: $(BUILD_DIR)/$(ASSETS_DIR)/weapon/f$$(subst 0_,_,$(subst 1_,_,%)).o | weapon-dirs
	$(call echo,Linking weapon/f$*,optional) $(LD) -r -b binary -o $@ $<
# weapon0.ld and weapon1.ld are not currently autogenerated
# Todo: This monstrosity of prereqs needs to be revised, but it works for now
$(BUILD_DIR)/weapon/%.elf: $(BUILD_DIR)/$(SRC_DIR)/weapon/$$(subst 0_,_,$(subst 1_,_,%)).c.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/$$(subst 0_,_,$(subst 1_,_,%)).data.s.o $(BUILD_DIR)/$(ASM_DIR)/weapon/data/$$(subst 0_,_,$(subst 1_,_,%)).sbss.s.o
	$(muffle)$(call echo,Linking weapon/$*,optional)
	$(muffle)$(LD) $(LD_FLAGS) --no-check-sections -o $@ \
		-Map $(BUILD_DIR)/weapon/$*.map \
		-T $(firstword $(subst _, ,$(subst w,weapon,$*))).ld \
		-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).weapon.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).weapon.txt \
		$^

# Step 4/6 of build
$(addprefix $(BUILD_DIR)/,%.BIN %.bin %_raw.bin %.exe): $(BUILD_DIR)/$$(call get_filename,%,st,bo).elf
	$(muffle)$(call echo,Building $(notdir $@),optional) $(OBJCOPY) -O binary $< $@
$(addprefix $(BUILD_DIR:pspeu=no)/,F_%.BIN f_%.bin):
	$(muffle)$(call echo,Building $(notdir $@),optional) $(GFXSTAGE) e $(ASSETS_DIR)/$(call get_filename,$*,st/,boss/) $@
$(BUILD_DIR)/TT_%.BIN: $(BUILD_DIR)/tt_%_raw.bin
	$(muffle)$(call echo,Cooking $(notdir $@),optional) cp $< $@.tmp && truncate -c -s 40960 $@.tmp && mv $@.tmp $@
$(BUILD_DIR)/WEAPON0.BIN: $(WEAPON0_FILES)
	$(muffle)$(call echo,Merging WEAPON0 files,optional) cat $^ > $@
$(BUILD_DIR)/weapon/%.bin: $(BUILD_DIR)/weapon/%.elf
	$(muffle)$(call echo,Building $(subst $(BUILD_DIR)/,,$@),optional) $(OBJCOPY) -O binary $< $@
	$(muffle)$(if $(findstring w0, $*),dd status=none if=/dev/zero of=$@ bs=1 seek=12287 count=1 conv=notrunc)

# Step 5/6 of build
main: $(BUILD_DIR)/main.exe
	$(call echo,Finished building $@)
dra ric sel: %: $(BUILD_DIR)/$$(call to_upper,%).BIN
	$(call echo,Finished building $@)
weapon: $(BUILD_DIR)/WEAPON0.BIN | weapon-dirs
	$(call echo,Finished building $@)
$(filter-out sel,$(STAGES)): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
	$(call echo,Finished building $@)
$(BOSSES): %: $(BUILD_DIR)/$$(call to_upper,%).BIN $(BUILD_DIR)/F_$$(call to_upper,%).BIN
	$(call echo,Finished building $@)
tt_00%: $(BUILD_DIR)/TT_00%.BIN
	$(call echo,Finished building $@)

# Step 6/6 of build
build_us build_hd: $(call get_targets)

# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.json.o: $(ASSETS_DIR)/%.json
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)$(PYTHON) $(TOOLS_DIR)/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(muffle)$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)$(PYTHON) $(TOOLS_DIR)/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(muffle)$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s

$(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)mkdir -p $(dir $@); $(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.gfxbin.o: $(ASSETS_DIR)/%.gfxbin
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)mkdir -p $(dir $@); $(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<
$(BUILD_DIR)/$(ASSETS_DIR)/%.palbin.o: $(ASSETS_DIR)/%.palbin
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$@),optional)
	$(muffle)mkdir -p $(dir $@); $(LD) -r -b binary -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $<

$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o: $(ASSETS_DIR)/weapon/%.png
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$<) object file, optional)
	$(muffle)$(PYTHON) $(TOOLS_DIR)/png2bin.py $< $@
$(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.animset.o: $(ASSETS_DIR)/weapon/%.animset.json
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$<) object file, optional)
	$(muffle)$(TOOLS_DIR)/splat_ext/animset.py gen-asm $< $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*.animset.s -s g_Animset$(subst 1,,$(lastword $(subst _, ,$*)))
	$(muffle)$(AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)/$(ASSETS_DIR)/weapon/$*.animset.s

$(BUILD_DIR)/$(ASSETS_DIR)/%.png.o: $(ASSETS_DIR)/%.png
	$(muffle)$(call echo,Creating $(subst $(BUILD_DIR)/,,$@), optional)
	$(muffle)mkdir -p $(dir $@)
	$(muffle)$(PNG2S) encode $< \
		$(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s g_saveIcon$(lastword $(subst _, ,$*)) \
		$(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s g_saveIconPal$(lastword $(subst _, ,$*))
	$(muffle)$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.png.s
	$(muffle)$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.pal.s
	$(muffle)rm $(addprefix $(BUILD_DIR)/$(ASSETS_DIR)/,$*.png.s $*.pal.s)

# dra is the only folder for .dec and for now they are ignored
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.dec.o: $(ASSETS_DIR)/dra/%.dec
	$(muffle)touch $@
# For now ric png.o files are ignored
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.png.o: $(ASSETS_DIR)/ric/%.png
	$(muffle)touch $@
# anything from MAD is an exception and it should be ignored
$(BUILD_DIR)/$(ASSETS_DIR)/st/mad/%.o:
	$(muffle)touch $@

# Adding psx targets to .PHONY and .SILENT
PHONY_TARGETS += $(addprefix extract_,us hd) $(call get_targets) build_us build_hd
MUFFLED_TARGETS += $(BUILD_DIR)/main.elf $(addprefix $(BUILD_DIR:pspeu=no)/,$(addsuffix .elf,$(filter-out main,$(GAME))))
MUFFLED_TARGETS += $(BUILD_DIR)/WEAPON0.BIN
# Muffled in link function: #$(BUILD_DIR)/st%.elf $(BUILD_DIR)/bo%.elf $(BUILD_DIR)/tt_%.elf
# Not muffled: tt_00%
# Muffled in target:
# main-dirs tt_%-dirs bo%-dirs st%-dirs weapon-dirs %-dirs
# $(BUILD_DIR:pspeu=no)/%.ld $(BUILD_DIR:pspeu=no)/st%.ld $(BUILD_DIR:pspeu=no)/bo%.ld
# $(ASM_DIR)/weapon/data/w_%.s $(BUILD_DIR)/%.s.o $(BUILD_DIR)/%.c.o $(BUILD_DIR)/$(SRC_DIR)/weapon/w_%.c.o
# $(BUILD_DIR)/weapon/f%.elf $(BUILD_DIR)/weapon/%.elf
# $(addprefix $(BUILD_DIR)/%,.BIN .bin _raw.bin .exe) $(addprefix $(BUILD_DIR:pspeu=no)/,F_%.BIN f_%.bin)
# $(BUILD_DIR)/TT_%.BIN $(BUILD_DIR)/weapon/%.bin
# $(BUILD_DIR)/$(ASSETS_DIR)/%.json.o $(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o
# $(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o $(BUILD_DIR)/$(ASSETS_DIR)/%.gfxbin.o $(BUILD_DIR)/$(ASSETS_DIR)/%.palbin.o
# $(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.o $(BUILD_DIR)/$(ASSETS_DIR)/weapon/%.animset.o
# $(BUILD_DIR)/$(ASSETS_DIR)/%.png.o
# $(BUILD_DIR)/$(ASSETS_DIR)/dra/%.dec.o $(BUILD_DIR)/$(ASSETS_DIR)/ric/%.png.o $(BUILD_DIR)/$(ASSETS_DIR)/st/mad/%.o
