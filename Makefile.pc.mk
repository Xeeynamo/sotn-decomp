CPP_PC := gcc
CPP_FLAGS_PC := -w -fsanitize=address -DVERSION_PC -DPERMUTER

C_FILES_PC := $(SRC_DIR)/pc/main.c $(SRC_DIR)/dra/91EBC.c $(SRC_DIR)/dra/92F60.c $(SRC_DIR)/dra/93290.c $(SRC_DIR)/dra/93BDC.c $(SRC_DIR)/dra/94F50.c $(SRC_DIR)/dra/953A0.c

build_pc:
	$(CPP_PC) $(CPP_FLAGS_PC) -I$(INCLUDE_DIR) -I$(SRC_DIR)/dra/ $(C_FILES_PC) -o $(BUILD_DIR)/sound.exe
