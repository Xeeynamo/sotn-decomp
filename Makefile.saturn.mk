# Saturn is special and does not yet conform
VERSION_PREFIX 	:= SATURN

# Extract targets is for when stages and bosses need to be prefixed with st and bo respectively
$(VERSION_PREFIX)_EXTRACT_TARGETS	:= $($(VERSION_PREFIX)_GAME) $(addprefix st,$($(VERSION_PREFIX)_STAGES)) $(addprefix bo,$($(VERSION_PREFIX)_BOSSES)) $($(VERSION_PREFIX)_SERVANTS)
# Build targets is for when the non-prefixed name is needed
$(VERSION_PREFIX)_BUILD_TARGETS	:= $($(VERSION_PREFIX)_GAME) $($(VERSION_PREFIX)_STAGES) $($(VERSION_PREFIX)_BOSSES) $($(VERSION_PREFIX)_SERVANTS)

SATURN_SPLITTER_DIR			:= $(TOOLS_DIR)/saturn-splitter
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

# Saturn specific targets
.PHONY: saturn
saturn: build_saturn check_saturn

.PHONY: build_saturn
build_saturn: $(SATURN_TOOLCHAIN)
	python3 ./tools/builds/saturn.py && ninja

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

$(BUILD_DIR)/lib/%.o: $(SRC_DIR)/saturn/lib/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(BUILD_DIR) && $(DOSEMU_APP) "GCC.EXE -c -I./ -O0 -m2 -fsigned-char lib/$*.c -o lib/$*.o"
$(BUILD_DIR)/%.o: $(SRC_DIR)/saturn/%.c $(CC1_SATURN)
	mkdir -p $(dir $@)
	cd $(BUILD_DIR) && $(DOSEMU_APP) "GCC.EXE -c -I./ -O2 -m2 -fsigned-char $*.c -o $*.o"

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
