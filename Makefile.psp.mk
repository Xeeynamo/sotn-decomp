WIBO            := bin/wibo
MWCCPSP         := bin/mwccpsp.exe

GNUASPSP        := mipsel-linux-gnu-as -I include/ -G0 -march=r6000 -mabi=eabi
MWASPSP         := $(WIBO) bin/asm_psp_elf.exe -gnu
ASPSP           := $(GNUASPSP)

GNULDPSP        := mipsel-linux-gnu-ld
MWLDPSP         := $(WIBO) bin/mwldpsp.exe -partial -nostdlib -msgstyle gcc -sym full,elf -g
LDPSP           := $(GNULDPSP)

MWCCGAP_DIR     := $(TOOLS_DIR)/mwccgap
MWCCGAP_APP     := $(MWCCGAP_DIR)/mwccgap.py
MWCCGAP         := $(PYTHON) $(MWCCGAP_APP)

PSP_BUILD_DIR   := build/pspeu
CCPSP           := MWCIncludes=bin/ $(WIBO) $(MWCCPSP)
PSP_EU_TARGETS  := stwrp tt_000
SPLAT_PIP       := splat split

MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -Op -c -lang c -sdatathreshold 0

define list_src_files_psp
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**))
endef

define list_o_files_psp
	$(foreach file,$(call list_src_files_psp,$(1)),$(PSP_BUILD_DIR)/$(file).o)
endef

build_pspeu: $(addsuffix _psp,$(PSP_EU_TARGETS))

extract_pspeu: $(addprefix $(PSP_BUILD_DIR)/,$(addsuffix .ld,$(PSP_EU_TARGETS)))

$(WIBO):
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check $(WIBO).sha256
	chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) bin/mwccpsp_219

$(MWCCGAP_APP):
	git submodule init $(MWCCGAP_DIR)
	git submodule update $(MWCCGAP_DIR)

$(PSP_BUILD_DIR)/%.c.o: %.c $(MWCCPSP) $(MWCCGAP_APP)
	mkdir -p $(dir $@)
	$(MWCCGAP) $< $@ --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --asm-dir-prefix asm/pspeu $(MWCCPSP_FLAGS)


$(PSP_BUILD_DIR)/asm/psp%.s.o: asm/psp%.s
	mkdir -p $(dir $@)
	$(ASPSP) -o $@ $<


$(PSP_BUILD_DIR)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	mkdir -p $(dir $@)
	mipsel-linux-gnu-ld -r -b binary -o $@ $<

tt_000_psp: $(PSP_BUILD_DIR)/tt_000.bin
stwrp_psp: $(PSP_BUILD_DIR)/wrp.bin

$(PSP_BUILD_DIR)/%.bin: $(PSP_BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@
$(PSP_BUILD_DIR)/wrp.bin: $(PSP_BUILD_DIR)/stwrp.elf
	$(OBJCOPY) -O binary $< $@

$(PSP_BUILD_DIR)/st%.ld: $(CONFIG_DIR)/splat.pspeu.st%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.st%.txt
	$(SPLAT_PIP) $<
$(PSP_BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.pspeu.tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.pspeu.tt_%.txt
	$(SPLAT_PIP) $<
$(PSP_BUILD_DIR)/tt_%.elf: $(PSP_BUILD_DIR)/tt_%.ld $$(call list_o_files_psp,servant/tt_$$*) $(PSP_BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link,tt_$*,$@)

ST_WRP_MERGE = st_update e_room_fg st_common st_debug e_breakable
$(PSP_BUILD_DIR)/stwrp.elf: $(PSP_BUILD_DIR)/stwrp.ld $(addprefix $(PSP_BUILD_DIR)/src/st/wrp/,$(addsuffix .c.o,$(ST_WRP_MERGE))) $$(call list_o_files_psp,st/wrp_psp) $(PSP_BUILD_DIR)/assets/st/wrp/mwo_header.bin.o
	$(call link,stwrp,$@)
