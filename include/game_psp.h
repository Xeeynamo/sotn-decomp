#include <common.h>

// This is just a guess, but it is required to have the correct struct size for
// PspUtilitySavedataParam
#define _PSP_FW_VERSION 200

// On PSP side this is compared against g_UserLanguage / 0x08B42058
// which is the system language of the console. Used to determine the
// language of various strings to display in-game
typedef enum {
    LANG_JP,
    LANG_EN,
    LANG_FR,
    LANG_SP,
    LANG_GE,
    LANG_IT,
} Language;

// PSP exclusive data symbols in PS.ELF
extern s32 D_psp_08B42044;
extern u32 D_psp_08B42050; // psp cross button
extern u32 D_psp_08B42054; // psp triangle button
extern s32 g_UserLanguage; // Defined in global address space
extern char* D_psp_08B42060;
extern s32 D_psp_08B42064;
extern s32 D_psp_08C62AA4;
extern bool D_psp_08C630C8;
extern s32 D_psp_08C630D0;
extern s32 D_psp_08C630D4;
extern s32 D_psp_08C630D8;
extern s32 D_psp_08C630DC;
extern u8 D_psp_08D39D3C[];
extern u_long D_psp_08D6DC40;
extern s32* D_psp_08D97C40;

// PSP exclusive functions in PS.ELF
void func_psp_0891CEB8(s32, s32);
void func_psp_0892667C(s32 paletteID, u16* palette);
float func_psp_089260AC(float);
float func_psp_089260D0(float);
u8* GetLangAt(s32 idx, u8* en, u8* fr, u8* sp, u8* ge, u8* it);

// PSP exclusive functions in DRA
void func_psp_091040A0(u_long** gfxBank);
void func_91040A0(u_long** gfxBank); // TODO replace with func_psp_091040A0
