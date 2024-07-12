#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <types.h>
#include <unkstruct.h>
#include <psxsdk/libgpu.h>

// PS1 and PSP use different values for these two
#ifndef VERSION_PSP
#define OTSIZE 0x200
#define MAXSPRT16 0x280
#endif
#ifdef VERSION_PSP
#define OTSIZE 0x600
#define MAXSPRT16 0x320
#endif
#define MAX_DRAW_MODES 0x400
#define MAX_TILE_COUNT 0x100
#define MAX_LINE_G2_COUNT 0x100
#define MAX_POLY_GT3_COUNT 0x30
#define MAX_POLY_GT4_COUNT 0x300
#define MAX_POLY_G4_COUNT 0x100
#define MAX_SPRT_COUNT 0x200
#define MAX_ENV_COUNT 0x10

typedef struct GpuBuffer { // also called 'DB' in the PSY-Q samples
    /* 0x00000 */ struct GpuBuffer* next;    // next chained buffer
    /* 0x00004 */ DRAWENV draw;              // drawing environment
    /* 0x0005C */ DISPENV disp;              // display environment
    /* 0x00074 */ DR_ENV env[MAX_ENV_COUNT]; // packed drawing environment
    /* 0x00474 */ OT_TYPE ot[OTSIZE];        // ordering table
    /* 0x00474 */ DR_MODE drawModes[MAX_DRAW_MODES];    // draw modes
    /* 0x03C74 */ POLY_GT4 polyGT4[MAX_POLY_GT4_COUNT]; // textured quads
    /* 0x0D874 */ POLY_G4 polyG4[MAX_POLY_G4_COUNT];    // untextured quads
    /* 0x0FC74 */ POLY_GT3 polyGT3[MAX_POLY_GT3_COUNT]; // textured triangles
    /* 0x103F4 */ LINE_G2 lineG2[MAX_LINE_G2_COUNT];    // lines
    /* 0x117F4 */ SPRT_16 sprite16[MAXSPRT16];          // tile map sprites
    /* 0x13FF4 */ TILE tiles[MAX_TILE_COUNT];           // squared sprites
    /* 0x14FF4 */ SPRT sprite[MAX_SPRT_COUNT];          // dynamic-size sprites
} GpuBuffer;                                            // size=0x177F4

typedef struct {
    /* 0x00 */ u32 drawModes;
    /* 0x04 */ u32 gt4;
    /* 0x08 */ u32 g4;
    /* 0x0C */ u32 gt3;
    /* 0x10 */ u32 line;
    /* 0x14 */ u32 sp16;
    /* 0x18 */ u32 tile;
    /* 0x1C */ u32 sp;
    /* 0x20 */ u32 env;
} GpuUsage;

typedef enum {
    GFX_BANK_NONE,
    GFX_BANK_4BPP,
    GFX_BANK_8BPP,
    GFX_BANK_16BPP,
    GFX_BANK_COMPRESSED,
} GfxBankKind;
#define GFX_TERMINATE() ((u_long*)-1) // can't be in GfxBankKind
#define GFX_ENTRY(x, y, w, h, data)                                            \
    (u_long*)((x) | ((y) << 16)), (u_long*)((w) | ((h) << 16)), (u_long*)data
typedef struct {
    /* 0x00 */ u_long* xy;
    /* 0x04 */ u_long* wh;
    /* 0x08 */ u_long* data;
} GfxEntry; // size=0xC

typedef struct {
    GfxBankKind kind;
    GfxEntry entries[0];
} GfxBank;

typedef struct {
    /* 0x0 */ GfxEntry* next;
    /* 0x4 */ u16 kind;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} GfxLoad; // size=0xC

extern GpuBuffer g_GpuBuffers[2];
extern s16 g_GpuBuffers_1_buf_draw_clip_y; // member of D_800542FC, TODO
                                           // overlap, hard to remove
extern GpuBuffer* g_CurrentBuffer;         // g_CurrentBuffer;
extern GfxLoad g_GfxLoad[0x10];
extern GpuUsage g_GpuUsage;

extern unkGraphicsStruct g_unkGraphicsStruct;

extern u8 g_Pix[4][128 * 128 / 2];

#endif // GRAPHICS_H
