// SPDX-License-Identifier: AGPL-3.0-or-later
#include <common.h>

// This is just a guess, but it is required to have the correct struct size for
// PspUtilitySavedataParam
#define _PSP_FW_VERSION 200

typedef enum {
    // stretches the game resolution to fill the PSP screen vertically
    SCREEN_MODE_FULL,

    // pixel perfect, but with borders around the game screen
    SCREEN_MODE_PERFECT,
} ScreenMode;

#define SB_TEMP_ADDR (s32) sceGeEdramGetAddr() + GU_VRAM_BUFSIZE * 3
#define SB_TEMP_WIDTH 0x100

#define SB_PS_ADDR SB_TEMP_ADDR + (0x200 * SB_TEMP_WIDTH)
#define SB_PS_WIDTH 0x200

#define SB_WOLF_ADDR SB_PS_ADDR + (0x201 * SB_PS_WIDTH)
#define SB_WOLF_WIDTH 0x40

#define WALLPAPER_TEX_ADDR (s32) sceGeEdramGetAddr() + 0x1BC000
#define WALLPAPER_CLUT_ADDR WALLPAPER_TEX_ADDR + (GU_VRAM_WIDTH * GU_SCR_HEIGHT)

#define SAVE_SLOT_COUNT 0xF

typedef struct {
    s8 name[SAVE_SLOT_COUNT][0x15];
    u8 data[SAVE_SLOT_COUNT][0x2000];
    s32 quickSaveSlot;
    u8 quickSaveData[0x2000];
} SoTNSaveData; // size: 0x20140

typedef struct {
    u8 unk0[0x10];
    u8 unlockedGames[3];
    u8 screenMode;
    u8 wallpaperIndex;
    u8 unk4[0x10];
    u8 unk5;
    u8 useAnalogStick;
    u8 unk7[0x969];
    SoTNSaveData sotnSaveData;
} DxCSaveData; // size: 0x20AD0

typedef enum {
    LOAD_DXC_SAVEDATA,
    AUTOLOAD_DXC_SAVEDATA,
    SAVE_DXC_SAVEDATA,
    AUTOSAVE_DXC_SAVEDATA,
    DELETE_ALL_DXC_SAVEDATA,
    GET_SIZES_DXC_SAVEDATA,
} DxCSaveDataTask;

typedef struct {
    int fileid;
    char version;
    char format;
    short n_pictures;
    char zero[8];
} Tm2Header;

typedef struct {
    int total_size;
    int clut_size;
    int image_size;
    ushort header_size;
    short clut_colors;
    char pict_format;
    char n_mipmaps;
    char clut_type;
    char image_type;
    ushort image_width;
    ushort image_height;
    int gs_tex0[2];
    int gs_tex1[2];
    int gs_regs;
    int gs_texclut;
} Tm2Pict;

typedef struct {
    u8* data;
    Tm2Header* headerPtr;
    Tm2Pict* pictPtr;
    u8* imagePtr;
    u8* clutPtr;
    s32 imageWidth;
} Picture; // size: 0x18

typedef struct {
    u32 c;
    float x, y, z;
} Vertex;

typedef struct {
    float u, v;
    u32 c;
    float x, y, z;
} TVertex;
