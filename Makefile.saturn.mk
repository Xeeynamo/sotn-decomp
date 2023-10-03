SATURN_BUILD_DIR	:= build/saturn
SATURN_ASSETS_DIR	:= assets/saturn
SATURN_OVL_TARGETS	:= GAME ALUCARD STAGE_02 WARP T_BAT
SATURN_LIB_TARGETS	:= lib/gfs lib/spr lib/dma lib/scl lib/csh lib/per lib/cdc lib/mth lib/bup lib/sys

DOSEMU						:= dosemu -quiet -dumb -f ./dosemurc -K . -E
SATURN_TOOLCHAIN			:= bin/cygnus-2.7-96Q3-bin
CC1_SATURN					:= $(SATURN_BUILD_DIR)/CC1.EXE
SATURN_SPLITTER_APP 		:= $(TOOLS_DIR)/saturn-splitter/rust-dis/target/release/rust-dis
SATURN_ADPCM_EXTRACT_APP	:= $(TOOLS_DIR)/saturn-splitter/adpcm-extract/target/release/adpcm-extract

SATURN_OVL_PRGS			:= $(addprefix $(SATURN_BUILD_DIR)/,$(addsuffix .PRG,$(SATURN_OVL_TARGETS)))
SATURN_LIB_OBJECTS		:= $(addprefix $(SATURN_BUILD_DIR)/,$(addsuffix .o,$(SATURN_LIB_TARGETS)))
SATURN_PCM_FILES 		:= $(wildcard disks/saturn/SD/*.PCM)
SATURN_WAV_FILES 		:= $(patsubst disks/saturn/SD/%.PCM,$(SATURN_ASSETS_DIR)/SD/%.wav,$(SATURN_PCM_FILES))

.PHONY: saturn
saturn: build_saturn check_saturn

.PHONY: check_saturn
check_saturn:
	sha1sum --check config/check.saturn.sha

.PHONY: build_saturn
build_saturn: $(SATURN_BUILD_DIR)/0.BIN $(SATURN_OVL_PRGS)

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
	bchunk disks/sotn.saturn.bin disks/sotn.saturn.cue disks/sotn.saturn.iso
	7z x disks/sotn.saturn.iso01.iso -odisks/saturn/ || true

.PHONY: extract_saturn_pcm
extract_saturn_pcm: $(SATURN_WAV_FILES)

.PHONY: diff_saturn
diff_saturn:
	sh-elf-objdump -z -m sh2 -b binary -D ./build/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-ours.txt && \
	sh-elf-objdump -z -m sh2 -b binary -D ./disks/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-theirs.txt && \
	diff ./build/saturn/$(FILENAME)-ours.txt ./build/saturn/$(FILENAME)-theirs.txt > ./build/saturn/$(FILENAME)-diff.txt || true

$(SATURN_BUILD_DIR)/0.BIN: $(SATURN_BUILD_DIR)/zero.elf
	sh-elf-objcopy $< -O binary $@
$(SATURN_BUILD_DIR)/GAME.PRG: $(SATURN_BUILD_DIR)/game.elf
	sh-elf-objcopy $< -O binary $@
$(SATURN_BUILD_DIR)/ALUCARD.PRG: $(SATURN_BUILD_DIR)/alucard.elf
	sh-elf-objcopy $< -O binary $@
$(SATURN_BUILD_DIR)/STAGE_02.PRG: $(SATURN_BUILD_DIR)/stage_02.elf
	sh-elf-objcopy $< -O binary $@
$(SATURN_BUILD_DIR)/WARP.PRG: $(SATURN_BUILD_DIR)/warp.elf
	sh-elf-objcopy $< -O binary $@
$(SATURN_BUILD_DIR)/T_BAT.PRG: $(SATURN_BUILD_DIR)/t_bat.elf
	sh-elf-objcopy $< -O binary $@

$(SATURN_BUILD_DIR)/zero.elf: $(SATURN_BUILD_DIR)/zero.o $(SATURN_LIB_OBJECTS) config/saturn/zero_syms.txt config/saturn/game_syms.txt config/saturn/zero_user_syms.txt
	cd $(SATURN_BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o zero.elf \
		-Map zero.map \
		-T ../../config/saturn/zero.ld \
		-T ../../config/saturn/zero_syms.txt \
		-T ../../config/saturn/game_syms.txt \
		-T ../../config/saturn/zero_user_syms.txt \
		zero.o $(addsuffix .o,$(SATURN_LIB_TARGETS))

$(SATURN_BUILD_DIR)/%.elf: $(SATURN_BUILD_DIR)/%.o config/saturn/zero_syms.txt config/saturn/game_syms.txt config/saturn/%_user_syms.txt
	cd $(SATURN_BUILD_DIR) && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o $*.elf \
		-Map $*.map \
		-T ../../config/saturn/$*.ld \
		-T ../../config/saturn/zero_syms.txt \
		-T ../../config/saturn/game_syms.txt \
		-T ../../config/saturn/$*_user_syms.txt \
		$*.o

$(SATURN_BUILD_DIR)/lib/%.o: $(SRC_DIR)/saturn/lib/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(SATURN_BUILD_DIR) && $(DOSEMU) "GCC.EXE -c -I./ -O0 -m2 -fsigned-char lib/$*.c -o lib/$*.o"
$(SATURN_BUILD_DIR)/%.o: $(SRC_DIR)/saturn/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(SATURN_BUILD_DIR) && $(DOSEMU) "GCC.EXE -c -I./ -O2 -m2 -fsigned-char $*.c -o $*.o"

$(CC1_SATURN): $(SATURN_TOOLCHAIN)
	mkdir -p $(dir $@)
	cp -r $(SATURN_TOOLCHAIN)/* $(SATURN_BUILD_DIR)
	cp  ./src/saturn/macro.inc $(SATURN_BUILD_DIR)
	cp -r ./src/saturn/*.c $(SATURN_BUILD_DIR)
	cp -r ./src/saturn/*.h $(SATURN_BUILD_DIR)
	cp -r ./src/saturn/lib $(SATURN_BUILD_DIR)/lib
	cp -r ./include/saturn $(SATURN_BUILD_DIR)/saturn
	mkdir -p $(SATURN_BUILD_DIR)/asm/saturn/
	cp -r ./asm/saturn/game $(SATURN_BUILD_DIR)/asm/saturn/game
	cp -r ./asm/saturn/t_bat $(SATURN_BUILD_DIR)/asm/saturn/t_bat
	cp -r ./asm/saturn/zero $(SATURN_BUILD_DIR)/asm/saturn/zero
	cp -r ./asm/saturn/stage_02 $(SATURN_BUILD_DIR)/asm/saturn/stage_02
	cp -r ./asm/saturn/warp $(SATURN_BUILD_DIR)/asm/saturn/warp
	cp -r ./asm/saturn/alucard $(SATURN_BUILD_DIR)/asm/saturn/alucard
	touch $(CC1_SATURN)

$(SATURN_SPLITTER_APP):
	git submodule init $(SATURN_SPLITTER_DIR)
	git submodule update $(SATURN_SPLITTER_DIR)
	cd $(SATURN_SPLITTER_DIR)/rust-dis && cargo build --release
	cd $(SATURN_SPLITTER_DIR)/adpcm-extract && cargo build --release

assets/saturn/SD/%.wav: disks/saturn/SD/%.PCM $(SATURN_SPLITTER_APP)
	mkdir -p $(ASSET_DIR)/saturn/SD
	$(SATURN_ADPCM_EXTRACT_APP) $< $@

# TODO: Remove me. Temporary backward compatibility with the CI
build_saturn_native: build_saturn
check_saturn_native: check_saturn
build_saturn_toolchain_native: extract_disk_saturn
