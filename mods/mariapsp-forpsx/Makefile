ROOT_DIR = ../..
SRC_DIR = $(ROOT_DIR)/src/maria
VERSION   ?= us
BUILD_DIR = build/$(VERSION)
TARGET = $(BUILD_DIR)/maria.elf
MAP = $(BUILD_DIR)/maria.map
OVERLAY = $(BUILD_DIR)/MARIA.BIN

CC = mipsel-linux-gnu-gcc
CFLAGS = -mno-abicalls -G0 -fno-pic -g -O2 -I$(ROOT_DIR)/include -I$(ROOT_DIR)/include/psxsdk -I$(ROOT_DIR)/src/maria -msoft-float -march=3000
CFLAGS += -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fno-stack-protector
CFLAGS += -DMARIA_SFX_MOD=1
ifeq ($(MARIA_SFX_DEBUG),1)
CFLAGS += -DMARIA_SFX_DEBUG=1
endif
LDFLAGS = -nostdlib -Wl,-Map=$(MAP) -Wl,--build-id=none -T symexport.txt -T $(ROOT_DIR)/player.ld -T $(ROOT_DIR)/config/undefined_syms.$(VERSION).txt -T $(BUILD_DIR)/symbols.txt

HEADER_SRC = maria.c
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(BUILD_DIR)/maria.o $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
ASSETS = $(BUILD_DIR)/.assets_done
PSP_DISK_DIR ?= $(ROOT_DIR)/disks/pspeu
PSP_SPK ?= $(PSP_DISK_DIR)/PSP_GAME/USRDIR/res/ps/snd_e/SE/sd_mar2.spk
SFX_DIR = $(BUILD_DIR)/sfx
SFX_STAMP = $(SFX_DIR)/.built
SFX_VH = $(SFX_DIR)/SD_RIH.VH
SFX_VB = $(SFX_DIR)/SD_RIH.VB


.PHONY: all build clean release disk

all: build

build: $(OVERLAY) $(SFX_STAMP)

$(BUILD_DIR):
	mkdir -p $@
$(ASSETS): $(BUILD_DIR)
	cd $(ROOT_DIR) && ./sotn.sh extract-assets config/assets.pspeu.yaml
	cd $(ROOT_DIR) && ./sotn.sh build-assets config/assets.pspeu.yaml
	touch $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR) $(ASSETS)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD_DIR)/maria.o: maria.c | $(BUILD_DIR) $(ASSETS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BUILD_DIR) $(ASSETS)
	sed 's;//.*;;' $(ROOT_DIR)/config/symbols.$(VERSION).txt > $(BUILD_DIR)/symbols.txt
	echo 'g_SfxData = 0x800BF554;' >> $(BUILD_DIR)/symbols.txt
	$(CC) $(LDFLAGS) -o $@ $^
$(OVERLAY): $(TARGET)
	mipsel-linux-gnu-objcopy -O binary $< $@
$(SFX_STAMP): $(PSP_SPK) $(ROOT_DIR)/tools/maria-sfx/src/main.rs $(ROOT_DIR)/tools/maria-sfx/Cargo.toml
	cargo run --quiet --manifest-path $(ROOT_DIR)/tools/maria-sfx/Cargo.toml -- build $(PSP_SPK) $(SFX_DIR)
	touch $@

clean:
	rm $(OVERLAY) $(MAP) $(BUILD_DIR)/symbols.txt $(ASSETS) $(TARGET) $(OBJS)

# prepare release by complying with the AGPL-3.0-or-later license
RELEASE_DIR = release
release: build
	test -f $(PSP_SPK)
	make $(OVERLAY)
	mkdir -p $(RELEASE_DIR)/src
	cp $(OVERLAY) $(RELEASE_DIR)/
	cp $(SFX_VH) $(SFX_VB) $(RELEASE_DIR)/
	cp $(MAP) $(RELEASE_DIR)/
	cp $(ROOT_DIR)/LICENSE $(RELEASE_DIR)/
	cp $$(find . -maxdepth 1 -type f) release/src/
	cp $$(find $(SRC_DIR) -maxdepth 1 -type f) release/src/
	cp $$(find $(ROOT_DIR)/include -maxdepth 1 -type f) release/src/
	cd release && sha256sum MARIA.BIN SD_RIH.VH SD_RIH.VB > SHA256SUMS

DISK_DIR = $(ROOT_DIR)/disks/mariapsp-forpsx
SOURCE_DISC ?= $(ROOT_DIR)/disks/sotn.$(VERSION).bin
disk: release $(SFX_STAMP)
	rm -rf $(DISK_DIR) || true
	cp -r $(RELEASE_DIR) $(DISK_DIR)
	cp "$(SOURCE_DISC)" $(DISK_DIR)/sotn-patched.$(VERSION).bin
	cd $(ROOT_DIR) && make bin/sotn-disk
	$(ROOT_DIR)/bin/sotn-disk inject $(DISK_DIR)/sotn-patched.$(VERSION).bin BIN/RIC.BIN $(OVERLAY)
	$(ROOT_DIR)/bin/sotn-disk inject $(DISK_DIR)/sotn-patched.$(VERSION).bin VAB/SD_RIH.VH $(SFX_VH)
	$(ROOT_DIR)/bin/sotn-disk inject $(DISK_DIR)/sotn-patched.$(VERSION).bin VAB/SD_RIH.VB $(SFX_VB)
