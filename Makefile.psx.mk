# Game OVL options: main dra ric weapon
# Both stage and reverse stage fall under "STAGES" variable, they are split only for readability.
# Stage OVL options: are cat cen chi dai dre lib mad no0 no1 no2 no3 no4 np3 nz0 nz1 sel st0 top wrp
# Reverse stage OVL options: rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp
# Boss OVL options: bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8
# Servant OVL options: tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006

ifeq ($(VERSION),us)
VERSION_PREFIX := PSX_US
else ifeq ($(VERSION),hd)
VERSION_PREFIX := PSX_HD
endif

PSX_US_GAME		:= main dra ric weapon
PSX_US_STAGES	:= cen chi dre lib no0 no1 no3 np3 nz0 st0 wrp mad sel no4
PSX_US_STAGES   += rwrp # Second line for stages for future readability
PSX_US_BOSSES   := bo4 mar
PSX_US_BOSSES   += rbo3 rbo5
PSX_US_SERVANTS	:= tt_000 tt_001 tt_002 tt_003 tt_004

# VERSION=hd
PSX_HD_GAME		:= dra ric
PSX_HD_STAGES	:= cen wrp
PSX_HD_STAGES	+= 
PSX_HD_BOSSES	:= 
PSX_HD_SERVANTS	:= tt_000

# Extract targets is for when stages and bosses need to be prefixed with st and bo respectively
$(VERSION_PREFIX)_EXTRACT_TARGETS	:= $($(VERSION_PREFIX)_GAME) $(addprefix st,$($(VERSION_PREFIX)_STAGES)) $(addprefix bo,$($(VERSION_PREFIX)_BOSSES)) $($(VERSION_PREFIX)_SERVANTS)
# Build targets is for when the non-prefixed name is needed
$(VERSION_PREFIX)_BUILD_TARGETS	:= $($(VERSION_PREFIX)_GAME) $($(VERSION_PREFIX)_STAGES) $($(VERSION_PREFIX)_BOSSES) $($(VERSION_PREFIX)_SERVANTS)

# compiler
CC1PSX          := ./bin/cc1-psx-26
CC              := $(CC1PSX)
AS              := $(CROSS)as
CPP             := $(CROSS)cpp
SOTNSTR			:= $(SOTNSTR_APP) process
MASPSX			 = $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=$(if $(findstring libgpu/sys.c.o,$@),2.21,2.34)

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

# PSX specific targets
extract.us: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSX_US_EXTRACT_TARGETS)))
	$(PNG2S) bdecode config/gfx.game.json disks/us assets/game
	make extract_assets
	make build_assets
extract.hd: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSX_HD_EXTRACT_TARGETS)))
	echo $(PSX_HD_EXTRACT_TARGETS)
	make extract_assets
	make build_assets

build.us: $(PSX_US_BUILD_TARGETS)
build.hd: $(PSX_HD_BUILD_TARGETS)

# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/main.ld: $(CONFIG_DIR)/splat.$(VERSION).main.yaml | main_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/dra.ld: $(CONFIG_DIR)/splat.$(VERSION).dra.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).dra.txt | dra_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/ric.ld: $(CONFIG_DIR)/splat.$(VERSION).ric.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).ric.txt | ric_dirs
	$(SPLAT) $<
	touch $@
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/stmad.ld: $(CONFIG_DIR)/splat.$(VERSION).stmad.yaml $(CONFIG_DIR)/symbols.beta.txt $(CONFIG_DIR)/symbols.stmad.txt | stmad_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/$(VERSION)/ST/MAD/F_MAD.BIN $(ASSETS_DIR)/st/mad
# todo: these should have an explicit dependency on extract disk
$(BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/$(VERSION)/ST/$$(echo '$*' | tr '[:lower:]' '[:upper:]')/F_$$(echo '$*' | tr '[:lower:]' '[:upper:]').BIN $(ASSETS_DIR)/st/$*
$(BUILD_DIR)/bo%.ld: $(CONFIG_DIR)/splat.$(VERSION).bo%.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).bo%.txt | bo%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/$(VERSION)/BOSS/$$(echo '$*' | tr '[:lower:]' '[:upper:]')/F_$$(echo '$*' | tr '[:lower:]' '[:upper:]').BIN $(ASSETS_DIR)/boss/$*
build/hd/st%.ld: $(CONFIG_DIR)/splat.$(VERSION).st%.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).st%.txt | st%_dirs
	$(SPLAT) $<
	$(GFXSTAGE) d disks/pspeu/PSP_GAME/USRDIR/res/ps/hdbin/f_$*.bin $(ASSETS_DIR)/st/$*
$(BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).tt_%.txt | tt_%_dirs
	$(SPLAT) $<
	touch $@
$(BUILD_DIR)/weapon.ld: $(CONFIG_DIR)/splat.$(VERSION).weapon.yaml $(CONFIG_DIR)/$(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt $(CONFIG_DIR)/symbols.$(VERSION).weapon.txt.in
	$(SPLAT) $<
	touch $@

$(BUILD_DIR)/dra.elf: $(call get_o_files,dra)
	$(call link,dra,$@)
$(BUILD_DIR)/tt_%.elf: $$(call get_o_files,servant/tt_$$*) | tt_%_dirs
	$(call link,tt_$*,$@)

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
	$(CPP) $(CPP_FLAGS) -lang-c $< | $(SOTNSTR) | $(ICONV) | $(CC) $(CC_FLAGS) $(PSXCC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

extract_assets: $(SOTNASSETS)
	$(SOTNASSETS) extract config/assets.$(VERSION).yaml
build_assets: $(SOTNASSETS)
	$(SOTNASSETS) build config/assets.$(VERSION).yaml

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
main: $(BUILD_DIR)/main.exe
.PHONY: %_dirs
main_dirs:
	$(foreach dir,$(MAIN_ASM_DIRS) $(MAIN_SRC_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))
$(BUILD_DIR)/main.exe: $(BUILD_DIR)/main.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/main.elf: $(MAIN_O_FILES) $(BUILD_DIR)/main.ld $(CONFIG_DIR)/undefined_syms.$(VERSION).txt $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).main.txt
	$(LD) $(LD_FLAGS) -o $@ \
	-Map $(BUILD_DIR)/main.map \
	-T $(BUILD_DIR)/main.ld \
	-T $(CONFIG_DIR)/undefined_syms.$(VERSION).txt \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).main.txt

# Game category structure
.PHONY: dra
dra: $(BUILD_DIR)/DRA.BIN
$(BUILD_DIR)/DRA.BIN: $(BUILD_DIR)/dra.elf
	$(OBJCOPY) -O binary $< $@

sel: $(BUILD_DIR)/SEL.BIN
$(BUILD_DIR)/SEL.BIN: $(BUILD_DIR)/stsel.elf
	$(OBJCOPY) -O binary $< $@

# Richter category structure
.PHONY: ric
ric: $(BUILD_DIR)/RIC.BIN
$(BUILD_DIR)/RIC.BIN: $(BUILD_DIR)/ric.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/ric.elf: $(call get_o_files,ric)
	$(call link,ric,$@)

# Stage category structure
.PHONY: cen
cen: $(BUILD_DIR)/CEN.BIN $(BUILD_DIR)/F_CEN.BIN
$(BUILD_DIR)/CEN.BIN: $(BUILD_DIR)/stcen.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_CEN.BIN:
	$(GFXSTAGE) e assets/st/cen $@

.PHONY: chi
chi: $(BUILD_DIR)/CHI.BIN $(BUILD_DIR)/F_CHI.BIN
$(BUILD_DIR)/CHI.BIN: $(BUILD_DIR)/stchi.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_CHI.BIN:
	$(GFXSTAGE) e assets/st/chi $@

.PHONY: dre
dre: $(BUILD_DIR)/DRE.BIN $(BUILD_DIR)/F_DRE.BIN
$(BUILD_DIR)/DRE.BIN: $(BUILD_DIR)/stdre.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_DRE.BIN:
	$(GFXSTAGE) e assets/st/dre $@

.PHONY: lib
lib: $(BUILD_DIR)/LIB.BIN $(BUILD_DIR)/F_LIB.BIN
$(BUILD_DIR)/LIB.BIN: $(BUILD_DIR)/stlib.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_LIB.BIN:
	$(GFXSTAGE) e assets/st/lib $@

.PHONY: mad
mad: $(BUILD_DIR)/MAD.BIN $(BUILD_DIR)/F_MAD.BIN
$(BUILD_DIR)/MAD.BIN: $(BUILD_DIR)/stmad.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_MAD.BIN:
	$(GFXSTAGE) e assets/st/mad $@

 PHONY: no0
no0: $(BUILD_DIR)/NO0.BIN $(BUILD_DIR)/F_NO0.BIN
$(BUILD_DIR)/NO0.BIN: $(BUILD_DIR)/stno0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NO0.BIN:
	$(GFXSTAGE) e assets/st/no0 $@

.PHONY: no1
no1: $(BUILD_DIR)/NO1.BIN $(BUILD_DIR)/F_NO1.BIN
$(BUILD_DIR)/NO1.BIN: $(BUILD_DIR)/stno1.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NO1.BIN:
	$(GFXSTAGE) e assets/st/no1 $@

.PHONY: no3
no3: $(BUILD_DIR)/NO3.BIN $(BUILD_DIR)/F_NO3.BIN
$(BUILD_DIR)/NO3.BIN: $(BUILD_DIR)/stno3.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NO3.BIN:
	$(GFXSTAGE) e assets/st/no3 $@

.PHONY: no4
no4: $(BUILD_DIR)/NO4.BIN $(BUILD_DIR)/F_NO4.BIN
$(BUILD_DIR)/NO4.BIN: $(BUILD_DIR)/stno4.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NO4.BIN:
	$(GFXSTAGE) e assets/st/no4 $@

.PHONY: np3
np3: $(BUILD_DIR)/NP3.BIN $(BUILD_DIR)/F_NP3.BIN
$(BUILD_DIR)/NP3.BIN: $(BUILD_DIR)/stnp3.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NP3.BIN:
	$(GFXSTAGE) e assets/st/np3 $@

.PHONY: nz0
nz0: $(BUILD_DIR)/NZ0.BIN $(BUILD_DIR)/F_NZ0.BIN
$(BUILD_DIR)/NZ0.BIN: $(BUILD_DIR)/stnz0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_NZ0.BIN:
	$(GFXSTAGE) e assets/st/nz0 $@

.PHONY: st0
st0: $(BUILD_DIR)/ST0.BIN $(BUILD_DIR)/F_ST0.BIN
$(BUILD_DIR)/ST0.BIN: $(BUILD_DIR)/stst0.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_ST0.BIN:
	$(GFXSTAGE) e assets/st/st0 $@

.PHONY: wrp
wrp: $(BUILD_DIR)/WRP.BIN $(BUILD_DIR)/F_WRP.BIN
$(BUILD_DIR)/WRP.BIN: $(BUILD_DIR)/stwrp.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_WRP.BIN:
	$(GFXSTAGE) e assets/st/wrp $@

.PHONY: rwrp
rwrp: $(BUILD_DIR)/RWRP.BIN $(BUILD_DIR)/F_RWRP.BIN
$(BUILD_DIR)/RWRP.BIN: $(BUILD_DIR)/strwrp.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_RWRP.BIN:
	$(GFXSTAGE) e assets/st/rwrp $@

# Boss category structure
.PHONY: bo4
bo4: $(BUILD_DIR)/BO4.BIN $(BUILD_DIR)/F_BO4.BIN
$(BUILD_DIR)/BO4.BIN: $(BUILD_DIR)/bobo4.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_BO4.BIN:
	$(GFXSTAGE) e assets/boss/bo4 $@

.PHONY: mar
mar: $(BUILD_DIR)/MAR.BIN $(BUILD_DIR)/F_MAR.BIN
$(BUILD_DIR)/MAR.BIN: $(BUILD_DIR)/bomar.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_MAR.BIN:
	$(GFXSTAGE) e assets/boss/mar $@

.PHONY: rbo3
rbo3: $(BUILD_DIR)/RBO3.BIN $(BUILD_DIR)/F_RBO3.BIN
$(BUILD_DIR)/RBO3.BIN: $(BUILD_DIR)/borbo3.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_RBO3.BIN:
	$(GFXSTAGE) e assets/boss/rbo3 $@

.PHONY: rbo5
rbo5: $(BUILD_DIR)/RBO5.BIN $(BUILD_DIR)/F_RBO5.BIN
$(BUILD_DIR)/RBO5.BIN: $(BUILD_DIR)/borbo5.elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/F_RBO5.BIN:
	$(GFXSTAGE) e assets/boss/rbo5 $@

# servant (familiar) targets
.PHONY: tt_000 tt_001 tt_002 tt_003 tt_004
tt_000: $(BUILD_DIR)/TT_000.BIN
tt_001: $(BUILD_DIR)/TT_001.BIN
tt_002: $(BUILD_DIR)/TT_002.BIN
tt_003: $(BUILD_DIR)/TT_003.BIN
tt_004: $(BUILD_DIR)/TT_004.BIN

$(BUILD_DIR)/TT_%.BIN: $(BUILD_DIR)/tt_%_raw.bin
	cp $< $@.tmp
	truncate -c -s 40960 $@.tmp
	mv $@.tmp $@
$(BUILD_DIR)/tt_%_raw.bin: $(BUILD_DIR)/tt_%.elf
	$(OBJCOPY) -O binary $< $@

.PHONY: %_dirs
tt_%_dirs:
	$(foreach dir,$(ASM_DIR)/servant/tt_$* $(ASM_DIR)/servant/tt_$*/data $(SRC_DIR)/servant/tt_$* $(ASSETS_DIR)/servant/tt_$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
bo%_dirs:
	$(foreach dir,$(ASM_DIR)/boss/$* $(ASM_DIR)/boss/$*/data $(ASM_DIR)/boss/$*/handwritten $(SRC_DIR)/boss/$* $(ASSETS_DIR)/boss/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
st%_dirs:
	$(foreach dir,$(ASM_DIR)/st/$* $(ASM_DIR)/st/$*/data $(ASM_DIR)/st/$*/handwritten $(SRC_DIR)/st/$* $(ASSETS_DIR)/st/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))
%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$* $(ASSETS_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/stmad.elf: $$(call get_o_files,st/mad) $$(call get_o_files,st,shared)
	$(LD) $(LD_FLAGS) -o $@ \
		-Map $(BUILD_DIR)/stmad.map \
		-T $(BUILD_DIR)/stmad.ld \
		-T $(CONFIG_DIR)/undefined_syms.beta.txt \
		-T $(CONFIG_DIR)/undefined_syms_auto.stmad.txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.stmad.txt
$(BUILD_DIR)/stsel.elf: $$(call get_o_files,st/sel,_st) $$(call get_o_files,st,_shared)
	$(call link,stsel,$@)
$(BUILD_DIR)/st%.elf: $$(call get_o_files,st/$$*,_st) $$(call get_o_files,st,_shared)
	$(call link,st$*,$@)
$(BUILD_DIR)/bo%.elf: $$(call get_o_files,boss/$$*,_st) $$(call get_o_files,boss,_shared)
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
	$(PYTHON) ./tools/png2bin.py $< $@

# Handles assets
$(BUILD_DIR)/$(ASSETS_DIR)/%.spritesheet.json.o: $(ASSETS_DIR)/%.spritesheet.json
	$(PYTHON) ./tools/splat_ext/spritesheet.py encode $< $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/dra/%.json.o: $(ASSETS_DIR)/dra/%.json
	$(PYTHON) ./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
	$(AS) $(AS_FLAGS) -o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.o $(BUILD_DIR)/$(ASSETS_DIR)/dra/$*.s
$(BUILD_DIR)/$(ASSETS_DIR)/ric/%.json.o: $(ASSETS_DIR)/ric/%.json
	$(PYTHON) ./tools/splat_ext/assets.py $< $(BUILD_DIR)/$(ASSETS_DIR)/ric/$*.s
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
$(BUILD_DIR)/$(ASSETS_DIR)/%.dec.o: $(ASSETS_DIR)/%.dec
# for now '.dec' files are ignored
	touch $@
$(BUILD_DIR)/$(ASSETS_DIR)/%.png.o: $(ASSETS_DIR)/%.png
	touch $@