#include "stage.h"
#include <psxsdk/romio.h>
#include "memcard.h"

#define DISP_W 512
#define DISP_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_H

#define NUM_MENU_OPTIONS 5
#define NUM_MENU_UNK_084 8

typedef enum {
    MAIN_MENU_CURSOR_INVALID = -1,
    MAIN_MENU_CURSOR_FILE_SELECT,
    MAIN_MENU_CURSOR_NAME_CHANGE,
    MAIN_MENU_CURSOR_FILE_COPY,
    MAIN_MENU_CURSOR_FILE_DELETE,
} MainMenuCursor;

typedef enum {
    GFX_UNK_0 = 0,
    GFX_UNK_1,
    GFX_FILE_SELECT,
    GFX_FILE_DELETE,
    GFX_NAME_CHANGE,
    GFX_FILE_COPY,
    GFX_UNK_6,

    GFX_WND_SAVE_SUMMARY = 11,
    GFX_UNK_12,
    GFX_WND_CARD_1,
    GFX_WND_CARD_2,
    GFX_UNK_15,
    GFX_UNK_16,
    GFX_UNK_17,
    GFX_UNK_18,
    GFX_UNK_19,
    GFX_UNK_20,
    NUM_GFX,
} MenuGfx;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8; // D_801D6A54
    s32* unkC;
    s32 unk10;
    s32 unk14; // D_801D6A60
    s16 unk18; // D_801D6A64
    s16 unk1A; // D_801D6A66
    s16 unk1C; // D_801D6A68
    s16 unk1E; // D_801D6A6A
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s32 unk28; // D_801D6A74
    s16 unk2C; // D_801D6A78
    s16 unk2E; // D_801D6A7A
    s16 unk30; // D_801D6A7C
    s16 unk32; // D_801D6A7E
    s32 unk34; // D_801D6A80
} Unkstruct_801B9B7C;

typedef struct {
    s32 unk00[16];
    s32 unk10[16];
    s32 unk20[32];
} Unkstruct_801BA498; /* size=0x100 */

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
    s32 padding;
} SaveSummary; /* size=0x3A4 */

extern const s32 D_801A7B8C[2];
extern s32 D_801BAF08; // block icon animation index
extern s32 D_801BAF20;
extern s32 D_801BAF30;
extern s32 D_801BB010;
extern s32 D_801BB014;
extern s32 g_InputCursorPos; // cursor Position
extern void* g_Cluts[];
extern void* g_EntityGfxs[];
extern s16** g_SpriteBanks[]; // g_SpriteBanks
extern void* D_8018C404;      // unknown type
extern u8 g_InputSaveName[9];

extern s32 D_80180040[];
extern s32 D_80180054[];
extern u8* D_801803A8;
extern u8* D_801803AC;
extern u8* D_801803B0;
extern u8* D_801803B4;
extern u8* D_801803BC;
extern u8* D_801803C0;
extern u8* D_801803C4; // images
extern u8* D_801803D0[];
extern s32 D_80180454[];
extern const u8* D_80180468; // pointer to D_801A7748 (string "richter ")
extern u8 D_8018046C[0x20 * 3];
extern s32 D_801804D0;
extern u8 D_801804D4[];
extern s32 D_801804D8[];
extern u8 D_80180504[];
extern u8 D_80180528[];
extern u8 D_80180564[];
extern u8 D_80180578[];
extern u8 D_80180580[];
extern const char* D_801808D0[];
extern s8 D_801823A0[]; // on-screen keyboard
extern RECT D_80182584;
extern RECT D_8018258C;
extern RECT D_801825A4;
extern s32 D_801962F4;
extern s32 D_801962F8[16];
extern s32 D_80196338[16];
extern s32 D_80196378;
extern s32 D_8019637C[32];
extern volatile u32* D_801963FC;
extern volatile u32* D_80196400;
extern volatile u32* D_80196404;
extern volatile u32* D_80196408;
extern volatile u32* D_8019640C;
extern volatile u32* D_80196410;
extern volatile u32* D_8019642C;
extern volatile u32* D_80196430;
extern volatile u32* D_80196434;
extern const u8 D_801A7748[];            // string "richter "
extern const u8 D_801A7754[12] ALIGNED4; // string "alucard "
extern s32 D_801A75A0[];
extern s32 D_801A75C0[];
extern const char D_801A7AF8[];           // rstep:%d,%d
extern const char D_801A7B08[];           // retry:%d
extern const char g_strMemcardRootPath[]; // "bu%1d%1d:"
extern const char g_MemcardSavePath[];    // "bu%1d%1d:%s"
extern const char D_801A802C[19];         // "BASLUS-00067DRAX00"
extern const char D_801ABF9C[];           // "MDEC_rest:bad option(%d)\n"
extern const char D_801ABFB8[];           // MDEC_in_sync
extern const char D_801ABFC8[];           // MDEC_out_sync
extern const char D_801ABFD8[];           // DMA=(%d,%d), ADDR=(0x%08x->0x%08x)
extern const char D_801AC000[];           // FIFO
extern const char D_801AC038[];           // "%s timeout:\n"
extern s32 D_801BAF10;
extern s32 D_801BAF14;
extern s32 D_801BAF18[][2];
extern s32 D_801BAF48;
extern s32 D_801BAFC0;
extern s32 D_801BAFC4;
extern u8* D_801BAFD0;
extern s32 D_801BAFD4;
extern s32 D_801BAFD8;
extern s32 D_801BAFDC;
extern s32 D_801BAFE0;
extern u32 D_801BAFE4;
extern s32 D_801BAFE8;
extern s32 g_memCardRStep;
extern s32 g_memCardRStepSub; // rstep sub
extern s32 g_memCardRetryCount;
extern s32 D_801BAFFC;
extern s32 D_801BB000;
extern s32 D_801BB004;
extern s32 D_801BB008;
extern s32 D_801BB00C;
extern s32 g_MemcardRetryCount;
extern s32 g_MemcardFd;
extern s32 D_801BC340;
extern s32 D_801BC344;
extern s16 D_801BC35A;
extern u16 D_801BC35C;
extern s16 D_801BC35E;
extern s16 D_801BC360;
extern s16 D_801BC362;
extern s16 D_801BC366;
extern s8 D_801BC36A;
extern s8 D_801BC36B;
extern s16 D_801BC390;
extern s16 D_801BC392;
extern s32 D_801BC394;
extern u32 D_801BC398[];
extern s32 D_801BC3D4[];
extern s32 g_MemCardSelectorX;
extern s32 g_MemCardSelectorY;
extern s32 D_801BC3E0; // on-screen keyboard key position
extern s32 D_801BC3E4;
extern s32 D_801BC3E8;
extern s32 D_801BC3EC; // selected memory card block
extern s32 D_801BC650;
extern s32 D_801BC8C8;
extern SaveSummary g_SaveSummary[PORT_COUNT];
extern s32 D_801BCC84[];
extern s32 D_801BD02C;
extern u32 D_801BD030;
extern s32 D_801D6B04;
extern s32 D_801D6B08;
extern s32 D_801D6B0C;
extern s32 g_MemcardBlockRead;
extern s32 g_MemcardStep;
extern s32 D_801D6B24;

extern Dialogue g_Dialogue;

void Update(void);
void HandleMainMenu(void);
void func_801ACBE4(s32 arg0, u16 arg1);
void func_801AD1D0(void);
void func_801AD218(void);
void func_801B2670(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height);
void DrawString16x16(const char* str, s32 x, s32 y, s32 tga);
void DrawImages8x8(u8* imgs, s32 x, s32 y, s32 tge);
void func_801B9C80(void);
void InitRoomEntities(s32 objLayoutId);
void func_801B60D4(void);
void func_801B17C8(void);
void func_801B1CFC(POLY_GT4* poly, s32 colorIntensity);
void func_801B26A0(
    POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v);
void func_801B1ED0();
void func_801B3A54(s32, s32);
s32 func_801B3A94(s32);
s32 _card_event_x();
void MemcardInit();
s32 func_800E9880(s32, s32);
void MDEC_rest(s32 option);
void func_801BA880();
void DecDCTvlc(s32, s32);
