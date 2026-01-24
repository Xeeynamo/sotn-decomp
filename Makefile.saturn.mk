# Saturn is special and does not yet conform
VERSION_PREFIX 	:= SATURN
SATURN_GAME		:= GAME ALUCARD RICHTER
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
SATURN_TOOLCHAIN			:= bin/cygnus-2.7-96Q3-bin
CC1_SATURN					:= $(BUILD_DIR)/CC1.EXE
SATURN_ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

SATURN_BUILD_PRGS		:= $(addprefix $(BUILD_DIR)/,$(addsuffix .PRG,$(SATURN_BUILD_TARGETS)))
SATURN_LIB_OBJECTS		:= $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SATURN_LIB_TARGETS)))
SATURN_PCM_FILES 		:= $(wildcard disks/saturn/SD/*.PCM)
SATURN_WAV_FILES 		:= $(patsubst disks/saturn/SD/%.PCM,$(SATURN_ASSETS_DIR)/SD/%.wav,$(SATURN_PCM_FILES))
DEPENDENCIES			+= $(SATURN_SPLITTER_APP)

# Saturn specific targets
.PHONY: saturn
saturn: build_saturn check_saturn

.PHONY: check # TODO: remove once `make saturn` in validate-and-report is merged to master
.PHONY: check_saturn
check_saturn:
	sha1sum --check config/check.saturn.sha

.PHONY: build_saturn
build_saturn: $(SATURN_TOOLCHAIN)
	python3 ./tools/builds/saturn.py && ninja

.PHONY: extract_saturn
extract_saturn: $(SATURN_SPLITTER_APP)
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/game.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/t_bat.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/zero.bin.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/stage_02.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/warp.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/alucard.prg.yaml
	$(SATURN_SPLITTER_APP) $(CONFIG_DIR)/saturn/richter.prg.yaml

.PHONY: extract_disk_saturn
extract_disk_saturn:
	bchunk disks/sotn.saturn.bin disks/sotn.saturn.cue disks/sotn.saturn.iso
	7z x disks/sotn.saturn.iso01.iso -odisks/saturn/ || true

.PHONY: extract_saturn_pcm
extract_saturn_pcm: $(SATURN_WAV_FILES)

.PHONY: diff_saturn
diff_saturn:
	sh-elf-objdump -z -m sh2 -b binary -D ./build/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-ours.txt && \
	sh-elf-objdump -z -m sh2 -b binary -D ./disks/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-theirs.txt && \
	diff ./build/saturn/$(FILENAME)-ours.txt ./build/saturn/$(FILENAME)-theirs.txt > ./build/saturn/$(FILENAME)-diff.txt || true

$(BUILD_DIR)/0.BIN: $(BUILD_DIR)/zero.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/GAME.PRG: $(BUILD_DIR)/game.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/ALUCARD.PRG: $(BUILD_DIR)/alucard.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/RICHTER.PRG: $(BUILD_DIR)/richter.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/STAGE_02.PRG: $(BUILD_DIR)/stage_02.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/WARP.PRG: $(BUILD_DIR)/warp.elf
	sh-elf-objcopy $< -O binary $@
$(BUILD_DIR)/T_BAT.PRG: $(BUILD_DIR)/t_bat.elf
	sh-elf-objcopy $< -O binary $@

$(BUILD_DIR)/zero.elf: $(BUILD_DIR)/zero.o $(SATURN_LIB_OBJECTS) config/saturn/zero_syms.txt config/saturn/game_syms.txt config/saturn/zero_user_syms.txt
	cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o zero.elf \
		-Map zero.map \
		-T ../../config/saturn/zero.ld \
		-T ../../config/saturn/zero_syms.txt \
		-T ../../config/saturn/game_syms.txt \
		-T ../../config/saturn/zero_user_syms.txt \
		zero.o $(addsuffix .o,$(SATURN_LIB_TARGETS))

$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o config/saturn/zero_syms.txt config/saturn/game_syms.txt config/saturn/%_user_syms.txt
	cd $(BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o $*.elf \
		-Map $*.map \
		-T ../../config/saturn/$*.ld \
		-T ../../config/saturn/zero_syms.txt \
		-T ../../config/saturn/game_syms.txt \
		-T ../../config/saturn/$*_user_syms.txt \
		$*.o

$(BUILD_DIR)/lib/%.o: $(SRC_DIR)/saturn/lib/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(BUILD_DIR) && $(DOSEMU_APP) "GCC.EXE -c -I./ -O0 -m2 -fsigned-char lib/$*.c -o lib/$*.o"
$(BUILD_DIR)/%.o: $(SRC_DIR)/saturn/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(BUILD_DIR) && $(DOSEMU_APP) "GCC.EXE -c -I./ -O2 -m2 -fsigned-char $*.c -o $*.o"

$(CC1_SATURN): $(SATURN_TOOLCHAIN)
	mkdir -p $(dir $@)
	cp -r $(SATURN_TOOLCHAIN)/* $(BUILD_DIR)
	cp  ./src/saturn/macro.inc $(BUILD_DIR)
	cp -r ./src/saturn/*.c $(BUILD_DIR)
	cp -r ./src/saturn/*.h $(BUILD_DIR)
	cp -r ./src/saturn/lib $(BUILD_DIR)/lib
	cp -r ./include/saturn $(BUILD_DIR)/saturn
	mkdir -p $(BUILD_DIR)/asm/saturn/
	cp -r ./asm/saturn/game $(BUILD_DIR)/asm/saturn/game
	cp -r ./asm/saturn/t_bat $(BUILD_DIR)/asm/saturn/t_bat
	cp -r ./asm/saturn/zero $(BUILD_DIR)/asm/saturn/zero
	cp -r ./asm/saturn/stage_02 $(BUILD_DIR)/asm/saturn/stage_02
	cp -r ./asm/saturn/warp $(BUILD_DIR)/asm/saturn/warp
	cp -r ./asm/saturn/alucard $(BUILD_DIR)/asm/saturn/alucard
	cp -r ./asm/saturn/richter $(BUILD_DIR)/asm/saturn/richter
	touch $(CC1_SATURN)

$(SATURN_SPLITTER_APP):
	git submodule init $(SATURN_SPLITTER_DIR)
	git submodule update $(SATURN_SPLITTER_DIR)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release

$(ASSETS_DIR)/saturn/SD/%.wav: disks/saturn/SD/%.PCM $(SATURN_SPLITTER_APP)
	mkdir -p $(ASSETS_DIR)/saturn/SD
	$(SATURN_ADPCM_EXTRACT_APP) $< $@

# Fixes build -j breaking due to dosemu
.NOTPARALLEL: build_saturn
