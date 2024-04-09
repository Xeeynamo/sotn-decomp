PSP_BUILD_DIR	:= build/pspeu
CCPSP			:= bin/wibo bin/mwccpsp.exe
PSP_EU_TARGETS	:= tt_000
SPLAT_PIP		:= splat split
MWCPP_APP		:= python3 tools/mwcpp.py

extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(PSP_EU_TARGETS)))

bin/wibo:
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check bin/wibo.sha256
	chmod +x bin/wibo
bin/mwccpsp.exe: bin/wibo bin/mwccpsp_3.0.1_147

$(PSP_BUILD_DIR)/tt_%.ld: $(CONFIG_DIR)/splat.$(VERSION).tt_%.yaml $(PSX_BASE_SYMS) $(CONFIG_DIR)/symbols.$(VERSION).tt_%.txt
	$(SPLAT_PIP) $<

$(PSP_BUILD_DIR)/%.c.o: %.c bin/mwccpsp.exe
	mkdir -p $(dir $@)
	$(MWCPP_APP) $< -o $@.processed
	$(CCPSP) -gccinc -Iinclude -D_internal_version_hd -O0 -c -g -o $@ $@.processed
	rm $@.processed

tt_000_psp: $(PSP_BUILD_DIR)/src/servant/tt_000_psp/80.c.o
