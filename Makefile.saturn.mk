# Saturn is special and does not yet conform
VERSION_PREFIX 	:= SATURN
SATURN_GAME		:= GAME ALUCARD
SATURN_STAGES	:= STAGE_02 WARP
SATURN_STAGES	+= 
SATURN_BOSSES 	:= 
SATURN_SERVANTS	:= T_BAT

# Extract targets is for when stages and bosses need to be prefixed with st and bo respectively
$(VERSION_PREFIX)_EXTRACT_TARGETS	:= $($(VERSION_PREFIX)_GAME) $(addprefix st,$($(VERSION_PREFIX)_STAGES)) $(addprefix bo,$($(VERSION_PREFIX)_BOSSES)) $($(VERSION_PREFIX)_SERVANTS)
# Build targets is for when the non-prefixed name is needed
$(VERSION_PREFIX)_BUILD_TARGETS	:= $($(VERSION_PREFIX)_GAME) $($(VERSION_PREFIX)_STAGES) $($(VERSION_PREFIX)_BOSSES) $($(VERSION_PREFIX)_SERVANTS)

SATURN_SPLITTER_DIR			:= $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP 		:= $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
SATURN_ASSETS_DIR := $(ASSETS_DIR)/saturn
SATURN_LIB_TARGETS	:= lib/gfs lib/spr lib/dma lib/scl lib/csh lib/per lib/cdc lib/mth lib/bup lib/sys

DOSEMU						:= dosemu
DOSEMU_FLAGS				:= -quiet -dumb -f ./dosemurc -K . -E
DOSEMU_APP					:= $(DOSEMU) $(DOSEMU_FLAGS)
SATURN_TOOLCHAIN			:= $(BIN_DIR)/cygnus-2.7-96Q3-bin
CC1_SATURN					:= $(BUILD_DIR)/CC1.EXE
SATURN_ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

SATURN_BUILD_PRGS		:= $(addprefix $(BUILD_DIR)/,$(addsuffix .PRG,$(SATURN_BUILD_TARGETS)))
SATURN_LIB_OBJECTS		:= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SATURN_LIB_TARGETS)))
SATURN_PCM_FILES 		:= $(wildcard $(RETAIL_DISK_DIR)/saturn/SD/*.PCM)
SATURN_WAV_FILES 		:= $(patsubst $(RETAIL_DISK_DIR)/saturn/SD/%.PCM,$(SATURN_ASSETS_DIR)/SD/%.wav,$(SATURN_PCM_FILES))
DEPENDENCIES			+= $(SATURN_SPLITTER_APP)

.PHONY: build_saturn
build_saturn: $(BUILD_DIR)/0.BIN $(SATURN_BUILD_PRGS)

.PHONY: extract_saturn
extract_saturn: $(SATURN_SPLITTER_APP)
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/game.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/t_bat.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/zero.bin.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/stage_02.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/warp.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/alucard.prg.yaml

.PHONY: extract_disk_saturn
extract_disk_saturn:
	bchunk $(RETAIL_DISK_DIR)/sotn.saturn.bin $(RETAIL_DISK_DIR)/sotn.saturn.cue $(RETAIL_DISK_DIR)/sotn.saturn.iso
	7z x $(RETAIL_DISK_DIR)/sotn.saturn.iso01.iso -o$(RETAIL_DISK_DIR)/saturn/ || true

.PHONY: extract_saturn_pcm
extract_saturn_pcm: $(SATURN_WAV_FILES)

.PHONY: diff_saturn
diff_saturn:
	sh-elf-objdump -z -m sh2 -b binary -D ./build/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-ours.txt && \
	sh-elf-objdump -z -m sh2 -b binary -D ./$(RETAIL_DISK_DIR)/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-theirs.txt && \
	diff ./build/saturn/$(FILENAME)-ours.txt ./build/saturn/$(FILENAME)-theirs.txt > ./build/saturn/$(FILENAME)-diff.txt || true

$(BUILD_DIR)/0.BIN: $(BUILD_DIR)/zero.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/GAME.PRG: $(BUILD_DIR)/game.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/ALUCARD.PRG: $(BUILD_DIR)/alucard.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/STAGE_02.PRG: $(BUILD_DIR)/stage_02.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/WARP.PRG: $(BUILD_DIR)/warp.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/T_BAT.PRG: $(BUILD_DIR)/t_bat.elf
	sh-elf-objcopy $< -O binary $@

$(BUILD_DIR)/zero.elf: $(BUILD_DIR)/zero.o $(SATURN_LIB_OBJECTS) $(CONFIG_DIR)/saturn/zero_syms.txt $(CONFIG_DIR)/saturn/game_syms.txt $(CONFIG_DIR)/saturn/zero_user_syms.txt
	cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o zero.elf \
		-Map zero.map \
		-T ../../$(CONFIG_DIR)/saturn/zero.ld \
		-T ../../$(CONFIG_DIR)/saturn/zero_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/game_syms.txt \
		-T ../../$(CONFIG_DIR)/saturn/zero_user_syms.txt \
		zero.o $(addsuffix .o,$(SATURN_LIB_TARGETS))

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
	git submodule init $(SATURN_SPLITTER_DIR)
	git submodule update $(SATURN_SPLITTER_DIR)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release

$(ASSETS_DIR)/saturn/SD/%.wav: $(RETAIL_DISK_DIR)/saturn/SD/%.PCM $(SATURN_SPLITTER_APP)
	mkdir -p $(ASSETS_DIR)/saturn/SD
	$(SATURN_ADPCM_EXTRACT_APP) $< $@

# Fixes build -j breaking due to dosemu
.NOTPARALLEL: build_saturn
