ROOT_DIR = ../..
SRC_DIR = $(ROOT_DIR)/src/maria
VERSION   ?= us
BUILD_DIR = build/$(VERSION)
TARGET = $(BUILD_DIR)/maria.elf

CC = mipsel-linux-gnu-gcc
CFLAGS = -mno-abicalls -G0 -fno-pic -Os -I$(ROOT_DIR)/include -I$(ROOT_DIR)/src/maria -msoft-float -march=3000
CFLAGS += -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm
LDFLAGS = -nostdlib -Wl,-Map=$(BUILD_DIR)/maria.map -T symexport.txt -T $(ROOT_DIR)/player.ld -T $(ROOT_DIR)/config/undefined_syms.$(VERSION).txt -T $(BUILD_DIR)/symbols.txt

HEADER_SRC = maria.c
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(BUILD_DIR)/maria.o $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
ASSETS = $(BUILD_DIR)/.assets_done


.PHONY: all clean

all: $(TARGET)

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
	mipsel-linux-gnu-objcopy -O binary $(TARGET) $(BUILD_DIR)/MARIA.BIN

clean:
	rm $(BUILD_DIR)/*
