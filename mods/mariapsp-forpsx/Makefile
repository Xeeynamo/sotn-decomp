ROOT_DIR = ../..
SRC_DIR = $(ROOT_DIR)/src/maria
VERSION   ?= us
BUILD_DIR = build/$(VERSION)
TARGET = $(BUILD_DIR)/maria.elf
MAP = $(BUILD_DIR)/maria.map
OVERLAY = $(BUILD_DIR)/MARIA.BIN

CC = mipsel-linux-gnu-gcc
CFLAGS = -mno-abicalls -G0 -fno-pic -g -O2 -I$(ROOT_DIR)/include -I$(ROOT_DIR)/src/maria -msoft-float -march=3000
CFLAGS += -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fno-stack-protector
LDFLAGS = -nostdlib -Wl,-Map=$(MAP) -Wl,--build-id=none -T symexport.txt -T $(ROOT_DIR)/player.ld -T $(ROOT_DIR)/config/undefined_syms.$(VERSION).txt -T $(BUILD_DIR)/symbols.txt

HEADER_SRC = maria.c
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(BUILD_DIR)/maria.o $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
ASSETS = $(BUILD_DIR)/.assets_done


.PHONY: all build clean release disk

all: build

build: $(OVERLAY)

$(BUILD_DIR):
	mkdir -p $@
$(ASSETS): $(BUILD_DIR)
	cd $(ROOT_DIR) && make bin/sotn-assets
	cd $(ROOT_DIR) && bin/sotn-assets extract config/assets.pspeu.yaml
	cd $(ROOT_DIR) && bin/sotn-assets build config/assets.pspeu.yaml
	touch $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR) $(ASSETS)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD_DIR)/maria.o: maria.c | $(BUILD_DIR) $(ASSETS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BUILD_DIR) $(ASSETS)
	sed 's;//.*;;' $(ROOT_DIR)/config/symbols.$(VERSION).txt > $(BUILD_DIR)/symbols.txt
	$(CC) $(LDFLAGS) -o $@ $^
$(OVERLAY): $(TARGET)
	mipsel-linux-gnu-objcopy -O binary $< $@

clean:
	rm $(OVERLAY) $(MAP) $(BUILD_DIR)/symbols.txt $(ASSETS) $(TARGET) $(OBJS)

# prepare release by complying with the AGPL-3.0-or-later license
RELEASE_DIR = release
release:
	cd $(ROOT_DIR) && VERSION=pspeu make extract_disk
	make $(OVERLAY)
	mkdir -p $(RELEASE_DIR)/src
	cp $(OVERLAY) $(RELEASE_DIR)/
	cp $(MAP) $(RELEASE_DIR)/
	cp $(ROOT_DIR)/LICENSE $(RELEASE_DIR)/
	cp $$(find . -maxdepth 1 -type f) release/src/
	cp $$(find $(ROOT_DIR)/src/maria -maxdepth 1 -type f) release/src/
	cp $$(find $(ROOT_DIR)/include -maxdepth 1 -type f) release/src/
	cd release && sha256sum MARIA.BIN > MARIA.BIN.sha256

DISK_DIR = $(ROOT_DIR)/disks/mariapsp-forpsx
disk: release
	rm -rf $(DISK_DIR) || true
	cp -r $(RELEASE_DIR) $(DISK_DIR)
	cp $(ROOT_DIR)/disks/sotn.$(VERSION).bin $(DISK_DIR)/sotn-patched.$(VERSION).bin
	cd $(ROOT_DIR) && make bin/sotn-disk
	$(ROOT_DIR)/bin/sotn-disk inject $(DISK_DIR)/sotn-patched.$(VERSION).bin BIN/RIC.BIN $(OVERLAY)
