TARGET              := sound
PC_BUILD_DIR	    := build/pc

CC_PC               := gcc
LD_PC               := ld
CC_FLAGS_PC         := -c -g -fPIC -DVERSION_PC -DPERMUTER -DNON_MATCHING -DHARD_LINK -fno-stack-protector 
CC_FLAGS_PC         += -DDEMO_KEY_PTR=0
CC_FLAGS_PC         += -I$(INCLUDE_DIR) -I$(SRC_DIR)/dra/ -I$(SRC_DIR)/pc/3rd
LD_FLAGS_PC         := -fsanitize=address -lc -lm -lSDL2

C_FILES_PC          := main.c log.c stubs.c sotn.c sim_pc.c
C_FILES_PC          += pc.c sdl2.c plat_unix.c stage_dummy.c stage_sel.c
C_FILES_PSX_SDK     := libgpu/ext.c
C_FILES_MOCK_SDK    := libapi.c libetc.c libgpu.c libgte.c libgs.c libcd.c libcard.c libspu.c libsnd.c cdc.c
C_FILES_3RD         := cJSON/cJSON.c
C_FILES_DRA         := 42398.c play.c loading.c pads.c
C_FILES_DRA         += save_mgr_pre.c save_mgr.c 4A538.c collider.c demo.c 5087C.c
C_FILES_DRA         += lba_stage.c config_us.c menu.c 5D5BC.c 627C4.c 63ED4.c
C_FILES_DRA         += 692E8.c 6D59C.c 704D0.c 71830.c 75DA0.c
C_FILES_DRA         += 91EBC.c 92F60.c 93290.c 93BDC.c 94F50.c 953A0.c
C_FILES_ST_SEL		:= banks.c CD54.c 2C048.c 33164.c 3410C.c 3585C.c 3642C.c

OBJS                := $(C_FILES_PC:%.c=$(PC_BUILD_DIR)/src/pc/%.o)
OBJS                += $(C_FILES_PSX_SDK:%.c=$(PC_BUILD_DIR)/src/main/psxsdk/%.o)
OBJS                += $(C_FILES_MOCK_SDK:%.c=$(PC_BUILD_DIR)/src/pc/psxsdk/%.o)
OBJS                += $(C_FILES_3RD:%.c=$(PC_BUILD_DIR)/src/pc/3rd/%.o)
OBJS                += $(C_FILES_DRA:%.c=$(PC_BUILD_DIR)/src/dra/%.o)
OBJS                += $(C_FILES_ST_SEL:%.c=$(PC_BUILD_DIR)/src/st/sel/%.o)

.PHONY: build_pc
build_pc: $(PC_BUILD_DIR)/$(TARGET)

.PHONY: clean_pc
clean_pc:
	rm -rf $(PC_BUILD_DIR)

$(PC_BUILD_DIR)/$(TARGET): $(OBJS)
	gcc $(LD_FLAGS_PC) -o $(PC_BUILD_DIR)/$(TARGET) $(OBJS)

$(PC_BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC_PC) $(CC_FLAGS_PC) -o $@ $<
