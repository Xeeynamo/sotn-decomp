DOSEMU				:= dosemu -quiet -dumb -f ./dosemurc -K . -E
SATURN_TOOLCHAIN	:= build/saturn/CC1.EXE
SATURN_SPLITTER_DIR := $(TOOLS_DIR)/saturn-splitter
SATURN_SPLITTER_APP := $(SATURN_SPLITTER_DIR)/rust-dis/target/release/rust-dis
SATURN_ADPCM_EXTRACT_APP := $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

SATURN_OVL_TARGETS  := GAME ALUCARD STAGE_02 WARP T_BAT
SATURN_OVL_PRGS     := $(addprefix build/saturn/,$(addsuffix .PRG,$(SATURN_OVL_TARGETS)))
SATURN_LIB_TARGETS := lib/gfs lib/spr lib/dma lib/scl lib/csh lib/per lib/cdc lib/mth lib/bup lib/sys
SATURN_LIB_OBJECTS  := $(addprefix build/saturn/,$(addsuffix .o,$(SATURN_LIB_TARGETS)))

.PHONY: check_saturn
check_saturn:
	sha1sum --check config/check.saturn.sha

.PHONY: build_saturn
build_saturn: build/saturn/0.BIN $(SATURN_OVL_PRGS)

.PHONY: extract_saturn_pcm
extract_saturn_pcm: $(SATURN_WAV_FILES)

build/saturn/0.BIN: build/saturn/zero.elf
	sh-elf-objcopy $< -O binary $@
build/saturn/GAME.PRG: build/saturn/game.elf
	sh-elf-objcopy $< -O binary $@
build/saturn/ALUCARD.PRG: build/saturn/alucard.elf
	sh-elf-objcopy $< -O binary $@
build/saturn/STAGE_02.PRG: build/saturn/stage_02.elf
	sh-elf-objcopy $< -O binary $@
build/saturn/WARP.PRG: build/saturn/warp.elf
	sh-elf-objcopy $< -O binary $@
build/saturn/T_BAT.PRG: build/saturn/t_bat.elf
	sh-elf-objcopy $< -O binary $@

build/saturn/zero.elf: build/saturn/zero.o $(SATURN_LIB_OBJECTS) config/saturn/zero_syms.txt config/saturn/game_syms.txt config/saturn/zero_user_syms.txt
	cd build/saturn && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o zero.elf \
		-Map zero.map \
		-T ../../config/saturn/zero.ld \
		-T ../../config/saturn/zero_syms.txt \
		-T ../../config/saturn/game_syms.txt \
		-T ../../config/saturn/zero_user_syms.txt \
		zero.o $(addsuffix .o,$(SATURN_LIB_TARGETS))

build/saturn/%.elf: build/saturn/%.o config/saturn/zero_syms.txt config/saturn/game_syms.txt config/saturn/%_user_syms.txt
	cd build/saturn && \
		sh-elf-ld -verbose --no-check-sections -nostdlib \
		-o $*.elf \
		-Map $*.map \
		-T ../../config/saturn/$*.ld \
		-T ../../config/saturn/zero_syms.txt \
		-T ../../config/saturn/game_syms.txt \
		-T ../../config/saturn/$*_user_syms.txt \
		$*.o

build/saturn/lib/%.o: $(SRC_DIR)/saturn/lib/%.c $(SATURN_TOOLCHAIN)
	mkdir -p $(dir $@)
	cd build/saturn && $(DOSEMU) "GCC.EXE -c -I./ -O0 -m2 -fsigned-char lib/$*.c -o lib/$*.o"
build/saturn/%.o: $(SRC_DIR)/saturn/%.c $(SATURN_TOOLCHAIN)
	mkdir -p $(dir $@)
	cd build/saturn && $(DOSEMU) "GCC.EXE -c -I./ -O2 -m2 -fsigned-char $*.c -o $*.o"

$(SATURN_TOOLCHAIN):
	mkdir -p $(dir $@)
	cp -r ./tools/saturn_toolchain/GCCSH/* $(SATURN_BUILD_DIR)
	cp  ./src/saturn/macro.inc $(SATURN_BUILD_DIR)
	cp -r ./src/saturn/*.c $(SATURN_BUILD_DIR)
	cp -r ./src/saturn/*.h $(SATURN_BUILD_DIR)
	cp -r ./src/saturn/lib $(SATURN_BUILD_DIR)/lib
	cp -r ./include/saturn $(SATURN_BUILD_DIR)/saturn
	mkdir -p $(SATURN_BUILD_DIR)/asm/saturn/
	mkdir -p $(SATURN_BUILD_DIR)/asm/saturn/
	cp -r ./asm/saturn/game $(SATURN_BUILD_DIR)/asm/saturn/game
	cp -r ./asm/saturn/t_bat $(SATURN_BUILD_DIR)/asm/saturn/t_bat
	cp -r ./asm/saturn/zero $(SATURN_BUILD_DIR)/asm/saturn/zero
	cp -r ./asm/saturn/stage_02 $(SATURN_BUILD_DIR)/asm/saturn/stage_02
	cp -r ./asm/saturn/warp $(SATURN_BUILD_DIR)/asm/saturn/warp
	cp -r ./asm/saturn/alucard $(SATURN_BUILD_DIR)/asm/saturn/alucard
	cp  ./tools/saturn_toolchain/compile_dosemu.sh $(SATURN_BUILD_DIR)
	chmod +x $(SATURN_BUILD_DIR)/compile_dosemu.sh


SATURN_PCM_FILES := $(wildcard disks/saturn/SD/*.PCM)
SATURN_WAV_FILES := $(patsubst disks/saturn/SD/%.PCM,build/saturn/SD/%.wav,$(SATURN_PCM_FILES))

assets/saturn/SD/%.wav: disks/saturn/SD/%.PCM $(SATURN_SPLITTER_APP)
	mkdir -p assets/saturn/SD
	$(SATURN_ADPCM_EXTRACT_APP) $< $@

build_saturn_native: build_saturn
check_saturn_native: check_saturn
