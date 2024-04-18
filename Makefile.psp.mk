PSP_BUILD_DIR	:= build/pspeu
CCPSP			:= bin/wibo bin/mwccpsp.exe
ASPSP			:= bin/wibo bin/asm_psp_elf.exe
PSP_EU_TARGETS	:= tt_000
SPLAT_PIP		:= splat split
MWCPP_APP		:= python3 tools/mwcpp.py

define list_o_files_psp
	$(foreach file,$(call list_src_files,$(1)),$(PSP_BUILD_DIR)/$(file).o)
endef

build_pspeu: tt_000_psp

extract_pspeu: $(addprefix $(PSP_BUILD_DIR)/,$(addsuffix .ld,$(PSP_EU_TARGETS)))

bin/wibo:
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check bin/wibo.sha256
	chmod +x bin/wibo
bin/mwccpsp.exe: bin/wibo bin/mwccpsp_3.0.1_147

$(PSP_BUILD_DIR)/src/%.o: src/%.c bin/mwccpsp.exe
	mkdir -p $(dir $@)
	$(MWCPP_APP) $< -o $@.processed
	$(CCPSP) \
		-gccinc \
		-Iinclude \
		-D_internal_version_hd \
		-O0 \
		-c \
		-lang c \
		-o $@ \
		$@.processed
	rm $@.processed
$(PSP_BUILD_DIR)/asm/%.o: asm/%.s bin/mwccpsp.exe
	mkdir -p $(dir $@)
	$(ASPSP) -gnu -o $@ $<

psptest: build/pspeu/asm/pspeu/servant/tt_000/header.o build/pspeu/src/servant/tt_000_psp/80.o build/pspeu/asm/pspeu/servant/tt_000/data/4C80.data.o build/pspeu/asm/pspeu/servant/tt_000/data/5E00.rodata.o
	bin/wibo bin/mwldpsp.exe \
		-partial \
		-nostdlib \
		-msgstyle gcc \
		-sym full,elf \
		-g \
		-o build/pspeu/tt_000.elf \
		-undefined config/symbols.pspeu.txt \
		-undefined config/undefined_syms_auto.pspeu.tt_000.txt \
		-undefined config/undefined_funcs_auto.pspeu.tt_000.txt \
		build/pspeu/src/servant/tt_000_psp/80.o \
		build/pspeu/asm/pspeu/servant/tt_000/data/4C80.data.o \
		build/pspeu/asm/pspeu/servant/tt_000/data/5E00.rodata.o

#tt_000_psp: $(PSP_BUILD_DIR)/src/servant/tt_000_psp/80.c.o
tt_000_psp: $(PSP_BUILD_DIR)/tt_000.bin

# NOTE: build/pspeu/header.bin is the first 0x80 bytes from the original tt_000.bin
$(PSP_BUILD_DIR)/tt_%.bin: $(PSP_BUILD_DIR)/tt_%.elf
	$(OBJCOPY) -O binary $< $@.tmp
	cat build/pspeu/header.bin $@.tmp > $@
	rm $@.tmp
$(PSP_BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.pspeu.tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.tt_%.txt
	$(SPLAT_PIP) $<
$(PSP_BUILD_DIR)/tt_%.elf: psptest
