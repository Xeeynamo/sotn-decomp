#include "stage.h"
#include <psxsdk/romio.h>
#include "memcard.h"

#define OVL_EXPORT(x) SEL_##x

#define DISP_W 512

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
    NUM_GFX,
} MenuGfx;

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
extern const char* D_801803A8[10];
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

extern s32 D_80180040[];
extern s32 D_80180054[];
extern const char* D_801803A8[];
extern const char* D_801803D0[];
extern const char* D_80180454[];
extern const char* D_80180468[];
extern u8 D_80180504[];
extern u8 D_80180528[];
extern u8 D_80180564[];
extern u8 D_80180578[];
extern u8 D_80180580[];
extern s8 D_801823A0[]; // on-screen keyboard
extern RECT D_80182584;
extern RECT D_8018258C;
extern RECT D_801825A4;
extern const char D_8018B304[];
extern s32 g_StreamWidth;
extern int g_StreamHeight;
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

extern const char D_801A7AF8[]; // rstep:%d,%d
extern const char D_801A7B08[]; // retry:%d
extern const char D_801ABF9C[]; // "MDEC_rest:bad option(%d)\n"
extern const char D_801ABFB8[]; // MDEC_in_sync
extern const char D_801ABFC8[]; // MDEC_out_sync
extern const char D_801ABFD8[]; // DMA=(%d,%d), ADDR=(0x%08x->0x%08x)
extern const char D_801AC000[]; // FIFO
extern const char D_801AC038[]; // "%s timeout:\n"
extern s32 D_801BAEE4[9];
extern s32 D_801BAF08; // block icon animation index
extern s32 D_801BAF0C;
extern s32 D_801BAF10;
extern s32 D_801BAF14;
extern s32 D_801BAF18[NUM_GFX][2];
extern s32 D_801BAFC0;
extern s32 MainMenuMaskPrimIndex;
extern s32 D_801BAFC8;
extern s32 D_801BAFCC;
extern u8* D_801BAFD0; // Pointer to texture pattern
extern s32 D_801BAFD4;
extern s32 D_801BAFD8;
extern s32 D_801BAFDC;
extern s32 D_801BAFE0;
extern u32 D_801BAFE4;
extern s32 D_801BAFE8;
extern s32 g_MemCardRStep;
extern s32 g_MemCardRStepSub; // rstep sub
extern s32 D_801BAFF4;
extern s32 g_MemCardRetryCount;
extern s32 D_801BAFFC;
extern s32 D_801BB000;
extern s32 D_801BB004;
extern s32 D_801BB008;
extern s32 D_801BB00C;
extern s32 D_801BB010;
extern s32 D_801BB014;
extern u16 D_801BB0F8[0x30][0x30];
extern const char D_8018BC54[];
extern s32 g_MemcardRetryCount;
extern s32 g_MemcardFd;
extern s32 D_801BC340;
extern s32 g_StreamDiskIsReady;
extern s32 D_801BC348;
extern s32 D_801BC34C;
extern s32 D_801BC350;
extern Dialogue g_Dialogue;
extern u32 D_801BC398[16];
extern s32 g_MemCardSelectorX;
extern s32 g_MemCardSelectorY;
extern s32 D_801BC3E0; // on-screen keyboard key position
extern s32 D_801BC3E4;
extern u32 D_801BC3E8;
extern s32 D_801BC3EC; // selected memory card block
extern s32 D_801BC650;
extern SaveSummary g_SaveSummary[PORT_COUNT];
extern u32 D_801BD030;
extern u32 g_StreamEndFrame;
extern u32 D_801BD03C;
extern u32 D_801BD040;
extern s32 g_StreamRewindSwitch[1];
extern u8 g_StreamImageBuffer[0x14000];
extern s32 D_801D104C[0x1680];
extern StreamEnv g_StreamEnv;
extern s32 D_801D6B04;
extern s32 g_InputCursorPos;
extern s32 D_801D6B0C;
extern s32 g_MemcardBlockRead;
extern char g_InputSaveName[12];
extern s32 g_MemcardStep;
extern s32 D_801D6B00;
extern s32 D_801D6B24;

void SEL_Update(void);
void HandleMainMenu(void);
void func_801ACBE4(s32 arg0, u16 arg1);
void func_801AD1D0(void);
void func_801AD218(void);
void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height);
void DrawString16x16(const char* str, s32 x, s32 y, s32 tga);
void DrawImages8x8(u8* imgs, s32 x, s32 y, s32 tge);
void func_801B9C80(void);
void SEL_Init(s32 objLayoutId);
void func_801B60D4(void);
void func_801B17C8(void);
void SetPrimGrey(Primitive* prim, s32 colorIntensity);
void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v);
void func_801B1ED0();
void func_801B3A54(s32, s32);
s32 func_801B3A94(s32);
s32 _card_event_x();
void MemcardInit();
s32 func_800E9880(s32, s32);
void MDEC_rest(s32 option);
void func_801BA880();
void DecDCTvlc(s32, s32);
