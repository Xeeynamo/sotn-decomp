#ifndef LAYER_H
#define LAYER_H

#include "types.h"

#define TILE_SIZE 16
#define TILE_MASK 0x0F
#define N_HORIZ_TILES 17
#define N_VERTI_TILES 16

#define LAYER_SHOW 1
#define LAYER_TPAGE_ID (0x20 | 0x40)
#define LAYER_SEMI_TRANS 0x80
#define LAYER_TPAGE_ALT 0x100
#define LAYER_CLUT_ALT 0x200
#define LAYER_WRAP_BG 0x1000

#define MAX_BG_LAYER_COUNT 16

typedef struct {
    /* 0x00 */ u8* gfxPage;
    /* 0x04 */ u8* gfxIndex;
    /* 0x08 */ u8* clut;
    /* 0x0C */ u8* collision;
} TileDefinition; // size = 0x10

typedef struct {
    /* 800730D8 0x00 */ u16* layout;
    /* 800730DC 0x04 */ TileDefinition* tileDef;
    /* 800730E0 0x08 */ f32 scrollX;
    /* 800730E4 0x0C */ f32 scrollY;
    /* 800730E8 0x10 */ u32 unused10;
    /* 800730EC 0x14 */ u32 unused14;
    /* 800730F0 0x18 */ u32 order;
    /* 800730F4 0x1C */ u32 flags;
    /* 800730F8 0x20 */ u32 w;
    /* 800730FC 0x24 */ u32 h;
    /* 80073100 0x28 */ u32 hideTimer;
    /* 80073104 0x2C */ u32 scrollKind;
} BgLayer; /* size=0x30 */

typedef struct {
    /* 80073084 */ u16* fg;
    /* 80073088 */ TileDefinition* tileDef;
    /* 8007308C */ f32 scrollX;
    /* 80073090 */ f32 scrollY;
    /* 80073094 */ s32 unused10;
    /* 80073098 */ s32 unused14;
    /* 8007309C */ s32 order;
    /* 800730A0 */ u32 flags;
    /* 800730A4 */ s32 hSize;
    /* 800730A8 */ s32 vSize;
    /* 800730AC */ u32 hideTimer;
    /* 800730B0 */ s32 left;
    /* 800730B4 */ s32 top;
    /* 800730B8 */ s32 right;
    /* 800730BC */ s32 bottom;
    /* 800730C0 */ s32 x;
    /* 800730C4 */ s32 y;
    /* 800730C8 */ s32 width;
    /* 800730CC */ s32 height;
    /* 800730D0 */ s32 unk30;
    /* 800730D4 */ s32 D_800730D4;
    /* 800730D8 */ BgLayer bg[MAX_BG_LAYER_COUNT];
} Tilemap;

extern Tilemap g_Tilemap;

typedef struct {
    /* D_8003C708 */ u16 flags;
    /* D_8003C70A */ u16 unk2;
    /* D_8003C70C */ u16 unk4;
    /* D_8003C70E */ s16 zPriority;
} FgLayer; /* size=0x8 */

extern FgLayer D_8003C708;

#endif // LAYER_H
