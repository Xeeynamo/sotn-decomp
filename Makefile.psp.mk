GNUASPSP		:= mipsel-linux-gnu-as -I include/ -G0 -march=r6000 -mabi=eabi 
MWASPSP			:= bin/wibo bin/asm_psp_elf.exe -gnu
ASPSP			:= $(GNUASPSP)

GNULDPSP		:= mipsel-linux-gnu-ld
MWLDPSP			:= bin/wibo bin/mwldpsp.exe -partial -nostdlib -msgstyle gcc -sym full,elf -g
LDPSP			:= $(GNULDPSP)

PSP_BUILD_DIR	:= build/pspeu
CCPSP			:= bin/wibo bin/mwccpsp.exe
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

$(PSP_BUILD_DIR)/%.c.o: %.c bin/mwccpsp.exe
	mkdir -p $(dir $@)
	$(MWCPP_APP) $< -o $@.processed
	$(CCPSP) \
		-gccinc \
		-Iinclude \
		-D_internal_version_hd \
		-O0 \
		-c \
		-lang c \
		-sdatathreshold 0 \
		-o $@ \
		$@.processed
	rm $@.processed
$(PSP_BUILD_DIR)/asm/%.s.o: asm/%.s
	mkdir -p $(dir $@)
	$(ASPSP) -o $@ $<

psptest: build/pspeu/src/servant/tt_000_psp/80.c.o build/pspeu/asm/pspeu/servant/tt_000/data/4C80.data.s.o build/pspeu/asm/pspeu/servant/tt_000/data/5E00.rodata.s.o build/pspeu/assets/servant/tt_000/header.bin.o
	$(LDPSP) \
    	-T build/pspeu/tt_000.ld \
    	-Map psp.map \
    	-T config/undefined_funcs_auto.pspeu.tt_000.txt \
    	-T config/undefined_syms_auto.pspeu.tt_000.txt \
		-o build/pspeu/tt_000.elf

build/pspeu/assets/servant/tt_000/header.bin.o:
	mkdir -p $(dir $@)
	mipsel-linux-gnu-ld -r -b binary -o build/pspeu/assets/servant/tt_000/header.bin.o assets/servant/tt_000/header.bin

tt_000_psp: $(PSP_BUILD_DIR)/tt_000.bin

# NOTE: build/pspeu/header.bin is the first 0x80 bytes from the original tt_000.bin
$(PSP_BUILD_DIR)/tt_%.bin: $(PSP_BUILD_DIR)/tt_%.elf
	$(OBJCOPY) -O binary $< $@
$(PSP_BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.pspeu.tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.tt_%.txt
	$(SPLAT_PIP) $<
$(PSP_BUILD_DIR)/tt_%.elf: psptest
