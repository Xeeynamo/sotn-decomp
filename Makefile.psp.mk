# Game OVL options: main dra ric weapon
# Both stage and reverse stage fall under "STAGES" variable, they are split only for readability.
# Stage OVL options: are cat cen chi dai dre lib mad no0 no1 no2 no3 no4 np3 nz0 nz1 sel st0 top wrp
# Reverse stage OVL options: rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp
# Boss OVL options: bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8
# Servant OVL options: tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006

GAME		:= dra
STAGES		:= lib no4 st0 wrp
STAGES		+= 
BOSSES		:= 
SERVANTS	:= tt_000

# Flags
AS_FLAGS        += -EL -I include/ -G0 -march=allegrex -mabi=eabi
MWCCPSP_FLAGS   := -gccinc -Iinclude -D_internal_version_$(VERSION) -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck
MWLDPSP_FLAGS   := -partial -nostdlib -msgstyle gcc -sym full,elf -g

# Tools
ALLEGREX_AS     := $(BIN_DIR)/allegrex-as
AS              := $(ALLEGREX_AS)
WIBO            := $(BIN_DIR)/wibo
MWCCPSP         := $(BIN_DIR)/mwccpsp.exe
CCPSP           := MWCIncludes=$(BIN_DIR) $(WIBO) $(MWCCPSP)

MWASPSP         := $(WIBO) $(BIN_DIR)/asm_psp_elf.exe -gnu
MWLDPSP         := $(WIBO) $(BIN_DIR)/mwldpsp.exe

MWCCGAP_DIR     := $(TOOLS_DIR)/mwccgap
MWCCGAP_APP     := $(MWCCGAP_DIR)/mwccgap.py
MWCCGAP         := $(PYTHON) $(MWCCGAP_APP)

DEPENDENCIES	+= $(ALLEGREX_AS)

# PSP specific targets
build_pspeu: $(call get_targets)
extract_pspeu: $(addprefix $(BUILD_DIR)/,$(addsuffix .ld,$(call get_targets,st,bo)))

$(WIBO):
	wget -O $@ https://github.com/decompals/wibo/releases/download/0.6.13/wibo
	sha256sum --check $(WIBO).sha256
	chmod +x $(WIBO)
$(MWCCPSP): $(WIBO) $(BIN_DIR)/mwccpsp_219

$(MWCCGAP_APP):
	git submodule update --init $(MWCCGAP_DIR)

$(call get_targets): %: $(BUILD_DIR)/%.bin

$(addprefix $(BUILD_DIR)/,%.BIN %.bin %_raw.bin): $(BUILD_DIR)/$$(call get_filename,%,st,bo).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.ld: $(CONFIG_DIR)/splat.$(VERSION).%.yaml $(BASE_SYMBOLS) $(CONFIG_DIR)/symbols.$(VERSION).%.txt
	$(SPLAT) $<

# This isn't ideal, but it works for now.
ST_DRA_MERGE = $(shell $(INLINE_PYTHON) $$'import yaml;\
import os;\
yaml_file=open(os.path.join(os.getcwd(),"config/splat.pspeu.dra.yaml"));\
config = yaml.safe_load(yaml_file);\
yaml_file.close();\
print(" ".join([x[2].split("/")[1] for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c" and x[2].startswith("dra/")]))')
$(BUILD_DIR)/dra.elf: $(BUILD_DIR)/dra.ld $(addprefix $(BUILD_DIR)/src/dra/,$(addsuffix .c.o,$(ST_DRA_MERGE))) $$(call list_o_files,dra_psp)
	$(call link,dra,$@)
$(BUILD_DIR)/tt_%.elf: $(BUILD_DIR)/tt_%.ld $$(call list_o_files,servant/tt_$$*) $(BUILD_DIR)/assets/servant/tt_%/mwo_header.bin.o
	$(call link,tt_$*,$@)

# This isn't ideal, but it works for now.
ST_LIB_MERGE = $(shell $(INLINE_PYTHON) $$'import yaml;\
import os;\
yaml_file=open(os.path.join(os.getcwd(),"config/splat.pspeu.stlib.yaml"));\
config = yaml.safe_load(yaml_file);\
yaml_file.close();\
print(" ".join([x[2].split("/")[1] for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c" and x[2].startswith("lib/")]))')
$(BUILD_DIR)/stlib.elf: $(BUILD_DIR)/stlib.ld $(addprefix $(BUILD_DIR)/src/st/lib/,$(addsuffix .c.o,$(ST_LIB_MERGE))) $$(call list_o_files,st/lib_psp) $(BUILD_DIR)/assets/st/lib/mwo_header.bin.o
	$(call link,stlib,$@)

# This isn't ideal, but it works for now.
ST_NO4_MERGE = $(shell $(INLINE_PYTHON) $$'import yaml;\
import os;\
yaml_file=open(os.path.join(os.getcwd(),"config/splat.pspeu.stno4.yaml"));\
config = yaml.safe_load(yaml_file);\
yaml_file.close();\
print(" ".join([x[2].split("/")[1] for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c" and x[2].startswith("no4/")]))')
$(BUILD_DIR)/stno4.elf: $(BUILD_DIR)/stno4.ld $(addprefix $(BUILD_DIR)/src/st/no4/,$(addsuffix .c.o,$(ST_NO4_MERGE))) $$(call list_o_files,st/no4_psp) $(BUILD_DIR)/assets/st/no4/mwo_header.bin.o
	$(call link,stno4,$@)

# This isn't ideal, but it works for now.
ST_ST0_MERGE = $(shell $(INLINE_PYTHON) $$'import yaml;\
import os;\
yaml_file=open(os.path.join(os.getcwd(),"config/splat.pspeu.stst0.yaml"));\
config = yaml.safe_load(yaml_file);\
yaml_file.close();\
print(" ".join([x[2].split("/")[1] for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c" and x[2].startswith("st0/")]))')
$(BUILD_DIR)/stst0.elf: $(BUILD_DIR)/stst0.ld $(addprefix $(BUILD_DIR)/src/st/st0/,$(addsuffix .c.o,$(ST_ST0_MERGE))) $$(call list_o_files,st/st0_psp) $(BUILD_DIR)/assets/st/st0/mwo_header.bin.o
	$(call link,stst0,$@)

# This isn't ideal, but it works for now.
ST_WRP_MERGE = $(shell $(INLINE_PYTHON) $$'import yaml;\
import os;\
yaml_file=open(os.path.join(os.getcwd(),"config/splat.pspeu.stwrp.yaml"));\
config = yaml.safe_load(yaml_file);\
yaml_file.close();\
print(" ".join([x[2].split("/")[1] for x in config["segments"][1]["subsegments"] if type(x) == list and x[1] == "c" and x[2].startswith("wrp/")]))')
$(BUILD_DIR)/stwrp.elf: $(BUILD_DIR)/stwrp.ld $(addprefix $(BUILD_DIR)/src/st/wrp/,$(addsuffix .c.o,$(ST_WRP_MERGE))) $$(call list_o_files,st/wrp_psp) $(BUILD_DIR)/assets/st/wrp/mwo_header.bin.o
	$(call link,stwrp,$@)

# Recipes
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

# Most of PSP is compiled with -O0, except part of DRA. This block selects the proper flag.
OPT_HIGH = -O4,p #need this because otherwise the comma breaks the if-statement
# Allow override. Any file in this list will get O4.
OPT_HI_OVERRIDES = 33F0.c.o A710.c.o C0B0.c.o EC60.c.o 186E8.c.o 61F30.c.o 624DC.c.o 628AC.c.o 63C90.c.o 64EE0.c.o
OPTIMIZATION = $(if $(filter $(notdir $@),$(OPT_HI_OVERRIDES)), $(OPT_HIGH), -Op)

$(BUILD_DIR)/%.c.o: %.c $(MWCCPSP) $(MWCCGAP_APP)
	@mkdir -p $(dir $@)
	$(MWCCGAP) $< $@ --mwcc-path $(MWCCPSP) --use-wibo --wibo-path $(WIBO) --as-path $(AS) --asm-dir-prefix asm/pspeu --macro-inc-path include/macro.inc $(MWCCPSP_FLAGS) $(OPTIMIZATION)

$(BUILD_DIR)/assets/%/mwo_header.bin.o: assets/%/mwo_header.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<
