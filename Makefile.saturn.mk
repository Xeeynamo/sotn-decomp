SATURN_SPLITTER_DIR			:= $(TOOLS_DIR)/saturn-splitter
SATURN_ASSETS_DIR			:= $(ASSETS_DIR)/saturn
SATURN_ADPCM_EXTRACT_APP	:= $(SATURN_SPLITTER_DIR)/adpcm-extract/target/release/adpcm-extract

SATURN_PCM_FILES	:= $(wildcard disks/saturn/SD/*.PCM)
SATURN_WAV_FILES	:= $(patsubst disks/saturn/SD/%.PCM,$(SATURN_ASSETS_DIR)/SD/%.wav,$(SATURN_PCM_FILES))

.PHONY: extract_saturn_pcm
extract_saturn_pcm: $(SATURN_WAV_FILES)

.PHONY: diff_saturn
diff_saturn:
	sh-elf-objdump -z -m sh2 -b binary -D ./build/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-ours.txt && \
	sh-elf-objdump -z -m sh2 -b binary -D ./disks/saturn/$(FILENAME) > ./build/saturn/$(FILENAME)-theirs.txt && \
	diff ./build/saturn/$(FILENAME)-ours.txt ./build/saturn/$(FILENAME)-theirs.txt > ./build/saturn/$(FILENAME)-diff.txt || true

$(ASSETS_DIR)/saturn/SD/%.wav: disks/saturn/SD/%.PCM $(SATURN_ADPCM_EXTRACT_APP)
	mkdir -p $(ASSETS_DIR)/saturn/SD
	$(SATURN_ADPCM_EXTRACT_APP) $< $@
