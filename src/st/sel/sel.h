#include "stage.h"
#include <psxsdk/romio.h>

#define DISP_W 512
#define DISP_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_H

extern s32 D_80180040[];
extern s32 D_80180054[];
extern u8* D_801803B0;
extern u8* D_801803B4;
extern s32 D_801BAF20;
extern s32 D_801BAF30;
extern s32 g_InputCursorPos; // cursor Position
void* g_Cluts[];
void* g_EntityGfxs[];
s16** g_SpriteBanks[]; // g_SpriteBanks
void* D_8018C404;      // unknown type
extern u8 g_InputSaveName[9];

void Update(void);
void TestCollisions(void);
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
void func_801B26A0(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
                   s32 v);

typedef struct {
    u32 unk0;
    u32 unk4;
} Unkstruct_801ACBE4;

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
    /* 0x000 */ s32 unk0;
    char pad4[0x3C - 0x4];
    /* 0x03C */ s32 unk3C;
    char pad40[0x78 - 0x40];
    /* 0x078 */ s32 areaId;
    char pad7C[0xB4 - 0x7C];
    /* 0x0B4 */ s32 unkB4;
    char padB8[0xF0 - 0xB8];
    /* 0x0F0 */ s32 level;
    char padF4[0x12C - 0xF4];
    /* 0x12C */ s32 money;
    char pad130[0x168 - 0x130];
    /* 0x168 */ s32 roomCount;
    char pad16C[0x1A4 - 0x16C];
    /* 0x1A4 */ s32 timerHours;
    char pad1A8[0x1E0 - 0x1A8];
    /* 0x1E0 */ s32 timerSeconds;
    char pad1E4[0x21C - 0x1E4];
    /* 0x21C */ s32 timerMinutes;
    char pad220[0x258 - 0x220];
    /* 0x258 */ s32 clearFlag;
    char pad25C[0x294 - 0x25C];
    /* 0x294 */ s32 player;
    char pad298[0x2D0 - 0x298];
    /* 0x2D0 */ char name[8];
    char pad2D8[0x3A8 - 0x2D8];
} SaveSummary; /* size=0x3A8 */

typedef struct {
    /* 0x000 */ u8 pad0[0x258];
    /* 0x258 */ u32 unk258;
    /* 0x25C */ u32 unk25C;
    /* 0x260 */ u8 pad260[0x18];
} Unkstruct_801B8A8C; /* size=0x278 */

extern u8* D_80180128[];
extern u8* D_8018012C[];
extern u8* D_801803A8;
extern u8* D_801803AC;
extern u8* D_801803BC;
extern u8* D_801803C0;
extern u8* D_801803C4; // images
extern s32 D_80180454[];
extern const u8* D_80180468; // pointer to D_801A7748 (string "richter ")
extern u8 D_8018046C[0x20 * 3];
extern u8 D_80180504[];
extern u8 D_80180528[];
extern /*?*/ s32 D_801808DC[];
extern u16 D_801808E4[];
extern u32 D_801822E4[];
extern s8 D_801823A0[]; // on-screen keyboard
extern RECT D_8018258C;
extern RECT D_801825A4;
extern s32 D_801962F4;
extern s32 D_801962F8[16];
extern s32 D_80196338[16];
extern s32 D_80196378;
extern s32 D_8019637C[32];
extern s32* D_801963FC;
extern s32* D_80196400;
extern s32* D_80196404;
extern s32* D_80196408;
extern s32* D_8019640C;
extern s32* D_80196410;
extern s32* D_8019642C;
extern s32* D_80196430;
extern s32* D_80196434;
extern const u8 D_801A7748[];            // string "richter "
extern const u8 D_801A7754[12] ALIGNED4; // string "alucard "
extern s32 D_801A75A0[];
extern s32 D_801A75C0[];
extern const char D_801A7AF8[];        // rstep:%d,%d
extern const char D_801A7B08[];        // retry:%d
extern const char D_801A7D78[];        // "bu%1d%1d:"
extern const char g_MemcardSavePath[]; // "bu%1d%1d:%s"
extern const char D_801A802C[18];      // "BASLUS-00067DRAX00"
extern const char D_801ABF9C[];        // "MDEC_rest:bad option(%d)\n"
extern const char D_801ABFB8[];        // MDEC_in_sync
extern const char D_801ABFC8[];        // MDEC_out_sync
extern const char D_801ABFD8[];        // DMA=(%d,%d), ADDR=(0x%08x->0x%08x)
extern const char D_801AC000[];        // FIFO
extern const char D_801AC038[];        // "%s timeout:\n"
extern s32 D_801BAF10;
extern Unkstruct_801ACBE4 D_801BAF18[];
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
extern s32 D_801BC2F8;
extern s32 D_801BC2FC;
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
extern Unkstruct_801B8A8C D_801BC3F0[];
extern s32 D_801BC650;
extern s32 D_801BC654[];
extern s32 D_801BC8C8;
extern s32 D_801BC8E0[];
extern SaveSummary D_801BC91C[15];
extern s32* D_801BC958[];
extern s32 D_801BCC84[];
extern s32 D_801BD02C;
extern u32 D_801BD030;
extern u32 D_801BD038; // StSetStream mode
extern s32 D_801BD044[];
extern s32 D_801D6B04;
extern s32 D_801D6B08;
extern s32 D_801D6B0C;
extern s32 D_801D6B20;
extern s32 D_801D6B24;

void func_801B1ED0();
void func_801B3A54(s32, s32);
s32 func_801B3A94(s32);
s32 _card_event_x();
void func_801B84F0();
s32 func_801B8A8C(s32, s32);
void MDEC_rest(s32 option);
void func_801BA880();
void MDEC_in_sync();
void MDEC_out_sync();
void MDEC_print_error(const char* funcName);
void func_801BABA4(s32, s32);