// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"
#include <psxsdk/romio.h>
#include "memcard.h"

#define OVL_EXPORT(x) SEL_##x

#define DISP_W 512

#define NUM_MENU_OPTIONS 5

typedef enum {
    MAIN_MENU_CURSOR_INVALID = -1,
    MAIN_MENU_CURSOR_FILE_SELECT,
    MAIN_MENU_CURSOR_NAME_CHANGE,
    MAIN_MENU_CURSOR_FILE_COPY,
    MAIN_MENU_CURSOR_FILE_DELETE,
} MainMenuCursor;

typedef enum {
    Tips_Generic,
    Tips_Input,
    Tips_YesNo,
    Tips_Confirm,
    Tips_MenuNavigation,
    Tips_NoYes,
} NavigationTips;

typedef enum {
    GFX_UNK_0 = 0,
    GFX_UNK_1,
    GFX_FILE_SELECT,
    GFX_FILE_DELETE,
    GFX_NAME_CHANGE,
    GFX_FILE_COPY,
    GFX_UNK_6,
    GFX_UNK_7,
    GFX_UNK_8,
    GFX_UNK_9,
    GFX_UNK_10,
    GFX_WND_SAVE_SUMMARY,
    GFX_UNK_12,
    GFX_WND_CARD_1,
    GFX_WND_CARD_2,
    GFX_UNK_15,
    GFX_UNK_16,
    GFX_UNK_17,
    GFX_UNK_18,
    GFX_UNK_19,
    GFX_UNK_20,
#ifdef VERSION_PSP
    GFX_UNK_21,
    GFX_UNK_22,
    GFX_UNK_23,
#endif
    NUM_GFX,
} MenuGfx;

// SEL seems to use these differently
typedef enum {
    Upd_Eng_Init,
    Upd_Eng_MenuInit = -1,
    Upd_Eng_MenuFadeIn = 1,
    Upd_Eng_MainMenuIdle,
    Upd_Eng_3,
    Upd_Eng_0x10 = 0x10,
    Upd_Eng_17,
    Upd_Eng_18,
    Upd_Eng_FileSelect = 0x30,
    Upd_Eng_49,
    Upd_Eng_50,
    Upd_Eng_51,
    Upd_Eng_64 = 0x40,
    Upd_Eng_65,
    Upd_Eng_FileCopy = 0x50,
    Upd_Eng_81,
    Upd_Eng_82,
    Upd_Eng_83,
    Upd_Eng_84,
    Upd_Eng_85,
    Upd_Eng_86,
    Upd_Eng_87,
    Upd_Eng_88,
    Upd_Eng_89,
    Upd_Eng_0x60 = 0x60,
    Upd_Eng_FileDelete = 0x70,
    Upd_Eng_113,
    Upd_Eng_114,
    Upd_Eng_115,
    Upd_Eng_116,
    Upd_Eng_117,
    Upd_Eng_118,
    Upd_Eng_119,
    Upd_Eng_120,
    Upd_Eng_0x80 = 0x80,
    Upd_Eng_NameChange = 0x90,
    Upd_Eng_145,
    Upd_Eng_146,
    Upd_Eng_147,
    Upd_Eng_148,
    Upd_Eng_149,
    Upd_Eng_150,
    Upd_Eng_151,
    Upd_Eng_152,
    Upd_Eng_153,
    Upd_Eng_0xA0 = 0xA0,
    Upd_Eng_0x100 = 0x100,
    Upd_Eng_257,
    Upd_Eng_258,
    Upd_Eng_259,
    Upd_Eng_260,
    Upd_Eng_0x200 = 0x200,
    Upd_Eng_513,
    Upd_Eng_514,
    Upd_Eng_515,
    Upd_Eng_516,
    Upd_Eng_0x210 = 0x210,
    Upd_Eng_529,
    Upd_Eng_530,
    Upd_Eng_531,
    Upd_Eng_532,
    Upd_Eng_0x220 = 0x220,
} SelGameEngineStep;

typedef struct {
    /* 801BC8E0 */ s32 icon[BLOCK_PER_CARD];
    /* 801BC91C */ u32 slot[BLOCK_PER_CARD];
    /* 801BC958 */ u32 stage[BLOCK_PER_CARD];
    /* 801BC994 */ u32 roomX[BLOCK_PER_CARD];
    /* 801BC9D0 */ u32 roomY[BLOCK_PER_CARD];
    /* 801BCA0C */ u32 level[BLOCK_PER_CARD];
    /* 801BCA48 */ u32 gold[BLOCK_PER_CARD];
    /* 801BCA84 */ u32 nRoomsExplored[BLOCK_PER_CARD];
    /* 801BCAC0 */ u32 playHours[BLOCK_PER_CARD];
    /* 801BCAFC */ u32 playSeconds[BLOCK_PER_CARD];
    /* 801BCB38 */ u32 playMinutes[BLOCK_PER_CARD];
    /* 801BCB74 */ u32 kind[BLOCK_PER_CARD]; // 0: play, 1: clear, 2: replay
    /* 801BCBB0 */ u32 character[BLOCK_PER_CARD];
    /* 801BCBEC */ char name[BLOCK_PER_CARD][10];
    s32 padding; // not really padding, it's a memory card status
} SaveSummary;   // size=0x3A8

typedef struct {
    const char* line1;
    const char* line2;
} StageName;

typedef struct {
    u_long* vlcbuf[2];  // 0x00
    int vlcid;          // 0x08
    u_short* imgbuf[2]; // 0x0c
    int imgid;          // 0x20
    RECT rect[2];       // 0x24
    int rectid;         // 0x32
    RECT slice;
    int isdone;
} DECENV;

typedef struct {
    DECENV dec;   // 4c
    DISPENV disp; // 84
    DRAWENV draw; // 98
    RECT rect;
    s32 unkFC;
} StreamEnv;

typedef struct {
    u32 cdOffset;
    u16 frameCount;
    u16 isRGB24;
} StreamInfo;

extern s32 g_CurrentStream;
extern StageName D_80180128[80];

extern const s32 D_801A7B8C[2];
extern void* g_Cluts[];
extern void* OVL_EXPORT(g_EntityGfxs)[];
extern StreamInfo g_StreamInfo0;
extern StreamInfo g_StreamInfo1;
extern StreamInfo g_StreamInfo2;
extern StreamInfo g_StreamInfo3;
extern StreamInfo* g_Streams[4];
extern s16** g_SpriteBanks[]; // g_SpriteBanks
extern void* D_8018C404[];    // unknown type

extern const char D_8018B304[];
extern s32 g_StreamWidth;
extern int g_StreamHeight;

extern const char D_801ABF9C[]; // "MDEC_rest:bad option(%d)\n"
extern const char D_801ABFB8[]; // MDEC_in_sync
extern const char D_801ABFC8[]; // MDEC_out_sync
extern const char D_801ABFD8[]; // DMA=(%d,%d), ADDR=(0x%08x->0x%08x)
extern const char D_801AC000[]; // FIFO
extern const char D_801AC038[]; // "%s timeout:\n"
extern const char D_8018BC54[];
extern s32 D_801BC3E4;
extern s32 D_801BC650;
extern SaveSummary g_SaveSummary[PORT_COUNT];
extern u32 g_StreamEndFrame;
extern u32 D_801BD03C;
extern u32 D_801BD040;
extern s32 g_StreamRewindSwitch[1];
extern u8 g_StreamImageBuffer[0x14000];
extern s32 D_801D104C[0x1680];
extern StreamEnv g_StreamEnv;
extern s32 g_MemcardBlockRead;
extern s32 g_MemcardStep;
extern s32 D_801D6B24;

void SEL_Update(void);
void HandleTitleScreen(void);
void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height);
void func_801B9C80(void);
void SEL_Init(s32 objLayoutId);
void func_801B60D4(void);
void func_801B17C8(void);
void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v);
void func_801B3A54(s32, s32);
s32 _card_event_x();
void MemcardInit();
void MDEC_rest(s32 option);
void func_801BA880();
void DecDCTvlc(s32, s32);
