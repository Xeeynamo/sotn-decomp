GNUASPSP		:= mipsel-linux-gnu-as -I include/ -G0 -march=r6000 -mabi=eabi 
MWASPSP			:= bin/wibo bin/asm_psp_elf.exe -gnu
ASPSP			:= $(GNUASPSP)

GNULDPSP		:= mipsel-linux-gnu-ld
MWLDPSP			:= bin/wibo bin/mwldpsp.exe -partial -nostdlib -msgstyle gcc -sym full,elf -g
LDPSP			:= $(GNULDPSP)

PSP_BUILD_DIR	:= build/pspeu
CCPSP			:= MWCIncludes=bin/ bin/wibo bin/mwccpsp.exe
PSP_EU_TARGETS	:= tt_000
SPLAT_PIP		:= splat split
MWCPP_APP		:= python3 tools/mwcpp.py

define list_src_files_psp
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1)_psp,$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**))
endef

define list_o_files_psp
	$(foreach file,$(call list_src_files_psp,$(1)),$(PSP_BUILD_DIR)/$(file).o)
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
	$(MWCPP_APP) $< -o $@.post.c
	$(CCPSP) -gccinc -Iinclude -D_internal_version_$(VERSION) -O0 -c -lang c -sdatathreshold 0 -o $@ $@.post.c
	rm $@.post.c
$(PSP_BUILD_DIR)/asm/psp%.s.o: asm/psp%.s
	mkdir -p $(dir $@)
	$(ASPSP) -o $@ $<


$(PSP_BUILD_DIR)/assets/servant/tt_000/header.bin.o: assets/servant/tt_000/header.bin
	mkdir -p $(dir $@)
	mipsel-linux-gnu-ld -r -b binary -o $@ $<

tt_000_psp: $(PSP_BUILD_DIR)/tt_000.bin

$(PSP_BUILD_DIR)/tt_%.bin: $(PSP_BUILD_DIR)/tt_%.elf
	$(OBJCOPY) -O binary $< $@
$(PSP_BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.pspeu.tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.tt_%.txt
	$(SPLAT_PIP) $<
$(PSP_BUILD_DIR)/tt_%.elf: $(PSP_BUILD_DIR)/tt_%.ld $$(call list_o_files_psp,servant/tt_$$*)
	$(call link,tt_$*,$@)

# cannot remove it for some reason? makefile bug?
_ignoreme_tt_000: $(PSP_BUILD_DIR)/src/servant/tt_000_psp/80.c.o $(PSP_BUILD_DIR)/asm/pspeu/servant/tt_000/data/4C80.data.s.o $(BUILD_DIR)/asm/pspeu/servant/tt_000/data/5E00.rodata.s.o
