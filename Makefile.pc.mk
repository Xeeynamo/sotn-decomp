TARGET              := sound
PC_BUILD_DIR	    := build/pc

CC_PC               := gcc
LD_PC               := ld
CC_FLAGS_PC         := -c -g -DVERSION_PC -DPERMUTER -DNON_MATCHING  -fno-stack-protector 
CC_FLAGS_PC         += -DDEMO_KEY_PTR=0
CC_FLAGS_PC         += -I$(INCLUDE_DIR) -I$(SRC_DIR)/dra/
LD_FLAGS_PC         := -fsanitize=address -lc -lm -lSDL2

C_FILES_PC          := main.c log.c stubs.c sotn.c
C_FILES_PC          += pc.c sdl2.c
C_FILES_PSX_SDK     := libapi.c libetc.c libgpu.c libgte.c libgs.c libcd.c libcard.c libspu.c libsnd.c cdc.c
C_FILES_DRA         := 42398.c play.c loading.c
C_FILES_DRA         += save_mgr_pre.c save_mgr.c 4A538.c collider.c demo.c
C_FILES_DRA         += menu.c
C_FILES_DRA         += 627C4.c 63ED4.c
C_FILES_DRA         += 91EBC.c 92F60.c 93290.c 93BDC.c 94F50.c 953A0.c

OBJS                := $(C_FILES_PC:%.c=$(PC_BUILD_DIR)/src/pc/%.o)
OBJS                += $(C_FILES_PSX_SDK:%.c=$(PC_BUILD_DIR)/src/pc/psxsdk/%.o)
OBJS                += $(C_FILES_DRA:%.c=$(PC_BUILD_DIR)/src/dra/%.o)

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
