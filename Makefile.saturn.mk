# Game OVL options: GAME ALUCARD
# Both stage and reverse stage fall under "STAGES" variable, they are split only for readability.
# Stage OVL options: STAGE_02 WARP
# Reverse stage OVL options: 
# Boss OVL options: 
# Servant OVL options: T_BAT
GAME		:= GAME ALUCARD
STAGES		:= STAGE_02 WARP
STAGES		+= 
BOSSES 		:= 
SERVANTS	:= T_BAT

LIB_OBJECTS 		:= lib/gfs.o lib/spr.o lib/dma.o lib/scl.o lib/csh.o lib/per.o lib/cdc.o lib/mth.o lib/bup.o lib/sys.o
ASSETS_DIR 			:= $(ASSETS_DIR)/saturn

DOSEMU				:= $(DOSEMU_APP) -quiet -dumb -f ./dosemurc -K . -E
OBJDUMP				:= sh-elf-objdump
OBJDUMP_FLAGS		:= -z -m sh2 -b binary -D
OBJCOPY				:= sh-elf-objcopy
CC1_SATURN			:= $(BUILD_DIR)/CC1.EXE
ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract
SATURN_SPLITTER 	:= $(SATURN_SPLITTER_APP)

EXTRACT_SATURN_FILES := $(subst 0,zero,0.bin) $(addsuffix .prg,$(call to_lower,$(call get_targets)))
PCM_FILES 			:= $(wildcard $(EXTRACTED_DISK_DIR)/SD/*.PCM)
WAV_FILES 			:= $(PCM_FILES:$(EXTRACTED_DISK_DIR)/SD/%.PCM=$(ASSETS_DIR)/SD/%.wav)

build_saturn: $(BUILD_DIR)/0.BIN $(addprefix $(BUILD_DIR)/,$(addsuffix .PRG,$(call get_targets)))

extract_saturn: $(EXTRACT_SATURN_FILES)
$(EXTRACT_SATURN_FILES): $(SATURN_SPLITTER_APP) $(EXTRACTED_DISK_DIR)
	$(SATURN_SPLITTER) $(CONFIG_DIR)/saturn/$@.yaml

extract_saturn_pcm: $(WAV_FILES)

diff_saturn:
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(BUILD_DIR)/$(FILENAME) > $(BUILD_DIR)/$(FILENAME)-ours.txt && \
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(EXTRACTED_DISK_DIR)/$(FILENAME) > $(BUILD_DIR)/$(FILENAME)-theirs.txt && \
	-diff $(BUILD_DIR)/$(FILENAME)-ours.txt $(BUILD_DIR)/$(FILENAME)-theirs.txt > $(BUILD_DIR)/$(FILENAME)-diff.txt

$(BUILD_DIR)/0.BIN: $(BUILD_DIR)/zero.elf
	$(call echo,Building $(notdir $@))
	$(OBJCOPY) $< -O binary $@
$(BUILD_DIR)/%.PRG: $(BUILD_DIR)/$$(call to_lower,%).elf
	$(call echo,Building $(notdir $@))
	$(muffle)$(OBJCOPY) $< -O binary $@

$(BUILD_DIR)/zero.elf: $(BUILD_DIR)/zero.o $(addprefix $(BUILD_DIR)/,$(LIB_OBJECTS)) $(CONFIG_DIR)/saturn/zero_syms.txt $(CONFIG_DIR)/saturn/game_syms.txt $(CONFIG_DIR)/saturn/zero_user_syms.txt
	$(call echo,Linking 0)
	$(muffle)cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o zero.elf \
		-Map zero.map \
		-T ../../$(CONFIG_DIR)/saturn/zero.ld \
		-T ../../$(CONFIG_DIR)/saturn/zero_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/game_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/zero_user_syms.txt \
		zero.o $(LIB_OBJECTS)

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o $(CONFIG_DIR)/saturn/zero_syms.txt $(CONFIG_DIR)/saturn/game_syms.txt $(CONFIG_DIR)/saturn/%_user_syms.txt
	$(call echo,Linking $*)
	$(muffle)cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o $*.elf \
		-Map $*.map \
		-T ../../$(CONFIG_DIR)/saturn/$*.ld \
		-T ../../$(CONFIG_DIR)/saturn/zero_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/game_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/$*_user_syms.txt \
		$*.o

$(BUILD_DIR)/lib/%.o: $(SRC_DIR)/saturn/lib/%.c $(CC1_SATURN)
	$(call echo,Compiling $(subst $(SRC_DIR),,$<))
	$(muffle)mkdir -p $(dir $@); cd $(BUILD_DIR) && $(DOSEMU) "GCC.EXE -c -I./ -O0 -m2 -fsigned-char lib/$*.c -o lib/$*.o"
$(BUILD_DIR)/%.o: $(SRC_DIR)/saturn/%.c $(CC1_SATURN)
	$(call echo,Linking $(subst $(SRC_DIR),,$<))
	$(muffle)mkdir -p $(dir $@); cd $(BUILD_DIR) && $(DOSEMU) "GCC.EXE -c -I./ -O2 -m2 -fsigned-char $*.c -o $*.o"

$(ASSETS_DIR)/SD/%.wav: $(EXTRACTED_DISK_DIR)/SD/%.PCM $(SATURN_SPLITTER_APP)
	$(call echo,Extracting $@)
	$(muffle)mkdir -p $(ASSETS_DIR)/SD; $(ADPCM_EXTRACT_APP) $< $@

$(CC1_SATURN): $(CYGNUS)
	mkdir -p $(dir $@)
	mkdir -p $(BUILD_DIR)/$(ASM_DIR)/
	cp -r $(CYGNUS)/* $(BUILD_DIR)
	cp  $(SRC_DIR)/saturn/macro.inc $(BUILD_DIR)
	cp -r $(SRC_DIR)/saturn/*.c $(BUILD_DIR)
	cp -r $(SRC_DIR)/saturn/*.h $(BUILD_DIR)
	cp -r $(SRC_DIR)/saturn/lib $(BUILD_DIR)/lib
	cp -r $(INCLUDE_DIR)/saturn $(BUILD_DIR)/$(INCLUDE_DIR)
	cp -r $(ASM_DIR)/game $(BUILD_DIR)/$(ASM_DIR)/game
	cp -r $(ASM_DIR)/t_bat $(BUILD_DIR)/$(ASM_DIR)/t_bat
	cp -r $(ASM_DIR)/zero $(BUILD_DIR)/$(ASM_DIR)/zero
	cp -r $(ASM_DIR)/stage_02 $(BUILD_DIR)/$(ASM_DIR)/stage_02
	cp -r $(ASM_DIR)/warp $(BUILD_DIR)/$(ASM_DIR)/warp
	cp -r $(ASM_DIR)/alucard $(BUILD_DIR)/$(ASM_DIR)/alucard
	touch $(CC1_SATURN)

# Fixes build -j breaking due to dosemu
.NOTPARALLEL: build_saturn

PHONY_TARGETS += build_saturn extract_saturn extract_saturn_pcm diff_saturn
MUFFLED_TARGETS += $(EXTRACT_SATURN_FILES) $(BUILD_DIR)/0.BIN $(BUILD_DIR)/zero.elf $(CC1_SATURN)
# Muffled in target: $(BUILD_DIR)/%.PRG $(BUILD_DIR)/%.elf $(BUILD_DIR)/lib/%.o $(BUILD_DIR)/%.o $(ASSETS_DIR)/SD/%.wav
