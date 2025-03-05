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

LIB_TARGETS	:= $(addprefix lib/, gfs spr dma scl csh per cdc mth bup sys)
LIB_OBJECTS	:= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(LIB_TARGETS)))

SATURN_SPLITTER_DIR	:= $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
SATURN_ASSETS_DIR 	:= $(ASSETS_DIR)/saturn

DOSEMU				:= dosemu
DOSEMU_FLAGS		:= -quiet -dumb -f ./dosemurc -K . -E
DOSEMU_APP			:= $(DOSEMU) $(DOSEMU_FLAGS)
SATURN_TOOLCHAIN	:= $(BIN_DIR)/cygnus-2.7-96Q3-bin
OBJDUMP				:= sh-elf-objdump
OBJDUMP_FLAGS		:= -z -m sh2 -b binary -D
SATURN_OBJCOPY				:= sh-elf-objcopy
CC1_SATURN			:= $(BUILD_DIR)/CC1.EXE
ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

PCM_FILES 			:= $(wildcard $(EXTRACTED_DISK_DIR)/SD/*.PCM)
WAV_FILES 			:= $(patsubst $(EXTRACTED_DISK_DIR)/SD/%.PCM,$(SATURN_ASSETS_DIR)/SD/%.wav,$(PCM_FILES))

.PHONY: build_saturn
build_saturn: $(BUILD_DIR)/0.BIN $(addprefix $(BUILD_DIR)/,$(addsuffix .PRG,$(call get_targets)))

.PHONY: extract_saturn
EXTRACT_SATURN := $(subst 0,zero,0.bin) $(addsuffix .prg,$(call to_lower,$(call get_targets)))
extract_saturn: $(SATURN_SPLITTER_APP)
	$(foreach item,$(EXTRACT_SATURN),$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/$(item).yaml;)

.PHONY: extract_saturn_pcm
extract_saturn_pcm: $(WAV_FILES)

.PHONY: diff_saturn
diff_saturn:
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(BUILD_DIR)/$(FILENAME) > $(BUILD_DIR)/$(FILENAME)-ours.txt && \
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(EXTRACTED_DISK_DIR)/$(FILENAME) > $(BUILD_DIR)/$(FILENAME)-theirs.txt && \
	-diff $(BUILD_DIR)/$(FILENAME)-ours.txt $(BUILD_DIR)/$(FILENAME)-theirs.txt > $(BUILD_DIR)/$(FILENAME)-diff.txt

$(BUILD_DIR)/0.BIN: $(BUILD_DIR)/zero.elf
	$(SATURN_OBJCOPY) $< -O binary $@
$(BUILD_DIR)/%.PRG: $(BUILD_DIR)/$$(call to_lower,%).elf
	$(SATURN_OBJCOPY) $< -O binary $@

$(BUILD_DIR)/zero.elf: $(BUILD_DIR)/zero.o $(LIB_OBJECTS) $(CONFIG_DIR)/saturn/zero_syms.txt $(CONFIG_DIR)/saturn/game_syms.txt $(CONFIG_DIR)/saturn/zero_user_syms.txt
	cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o zero.elf \
		-Map zero.map \
		-T ../../$(CONFIG_DIR)/saturn/zero.ld \
		-T ../../$(CONFIG_DIR)/saturn/zero_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/game_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/zero_user_syms.txt \
		zero.o $(addsuffix .o,$(LIB_TARGETS))

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o $(CONFIG_DIR)/saturn/zero_syms.txt $(CONFIG_DIR)/saturn/game_syms.txt $(CONFIG_DIR)/saturn/%_user_syms.txt
	cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o $*.elf \
		-Map $*.map \
		-T ../../$(CONFIG_DIR)/saturn/$*.ld \
		-T ../../$(CONFIG_DIR)/saturn/zero_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/game_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/$*_user_syms.txt \
		$*.o

$(BUILD_DIR)/lib/%.o: $(SRC_DIR)/saturn/lib/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(BUILD_DIR) && $(DOSEMU_APP) "GCC.EXE -c -I./ -O0 -m2 -fsigned-char lib/$*.c -o lib/$*.o"
$(BUILD_DIR)/%.o: $(SRC_DIR)/saturn/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(BUILD_DIR) && $(DOSEMU_APP) "GCC.EXE -c -I./ -O2 -m2 -fsigned-char $*.c -o $*.o"

$(CC1_SATURN): $(SATURN_TOOLCHAIN)
	mkdir -p $(dir $@)
	mkdir -p $(BUILD_DIR)/$(ASM_DIR)/
	cp -r $(SATURN_TOOLCHAIN)/* $(BUILD_DIR)
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

$(SATURN_SPLITTER_APP):
	git submodule update --init $(SATURN_SPLITTER_DIR)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release

$(SATURN_ASSETS_DIR)/SD/%.wav: $(EXTRACTED_DISK_DIR)/SD/%.PCM $(SATURN_SPLITTER_APP)
	mkdir -p $(SATURN_ASSETS_DIR)/SD
	$(ADPCM_EXTRACT_APP) $< $@

$(DOSEMU):
	cd $(TOOLS_DIR); \
	git clone https://github.com/sozud/dosemu-deb.git
	sudo dpkg -i $(TOOLS_DIR)/dosemu-deb/*.deb
	
# Fixes build -j breaking due to dosemu
.NOTPARALLEL: build_saturn
