#ifndef DRA_H
#define DRA_H
#include "main.h"

typedef struct {
    unsigned int unk0;
    unsigned int unk4;
    short x0,y0;
    short unkC,unkE;
    unsigned int unk10;
    short x1,y1;
    unsigned int unk18;
    unsigned int unk1c;
    short unk20,unk22;
    unsigned int unk24;
    unsigned int unk28;
    short unk2C,unk2E;
} UnkPoly;

typedef struct
{
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} Rect;

typedef struct
{
    Rect tag, unk1;
    int w;
    int unk14;
    int unk18;
} MenuContext;

typedef struct 
{
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Unkstruct1;

extern s32 D_8006C39C;
extern s32 D_8006C3A0;
extern s32 D_80073060;
extern s32 D_80073080;
extern s16 D_80073404;
extern s16 D_80073406;
extern s8  D_80073510;
extern s8  D_80073511;
extern s8  D_80073512;
extern Unkstruct1 D_80097490;
extern u16 D_80097494;
extern s16 D_80097496;
extern s32 D_800974A0;
extern s32 D_800974AC;
extern u8  D_8009798A;
extern u8  D_80097A8D;

extern s32 D_800A4B04;
extern s32 D_800A7718;
extern u16 D_800A7734;
extern u8  D_80137460;
extern s8  D_80137638;
extern s32 D_80137844;
extern s32 D_80137848;
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 D_80137E4C;
extern s32 D_80137E64;
extern s32 D_80137E68;
extern s32 D_80138F20;
extern s32 D_80138F7C;
extern s16 D_8013901C;
extern s8  D_80139020;
extern s16 D_801396EA;
extern u16 D_801396F4;
extern s32 D_8013980C;
extern u8  D_80139810;
extern s32 D_80139828;
extern s32 D_8013B158;
extern s32 D_8013B3D0;
extern s32 D_8013B5E8;
extern s16 D_8013B61C;
extern s32 D_8013B660;
extern s16 D_8013B668;
extern s32 D_8013B694;
extern s32 D_80138784[487];

void func_800E4124(s32 arg0);
void func_800E8D24(void);
void func_800E8DF0(void);
void func_800E92E4(void);
void func_800E92F4(void);
void func_800EA5E4(s32);
void func_800EDA70(s32 *arg0);
void func_800EDAE4(void);
void func_800F4994(void);
void func_800F4F48(void);
void func_800F4FD0(void);
void func_800F53A4(void);
s32 IsSpriteOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* a5);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void func_800F5904(void*, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v, s32 unk1, s32 unk2, bool disableTexShade, s32 unk4);
s32 func_800F62E8(s32 arg0);
void drawMenuChar(s32 ch, int x, int y, void* context);
void func_800FABEC(s32 arg0);
void func_800FAC30(void);
s32 func_800FD664(s32 arg0);
u8 *func_800FD744(s32 arg0);
u8 *func_800FD760(s32 arg0);
s32 func_800FD77C(s32 arg0, s32 arg1);
void func_800FD874(u16 arg0, s32 arg1);
void func_800FDE00(void);
void func_800FF0A0(s32 arg0);
void func_80102DEC(s32 arg0);
void func_80103EAC(void);
void func_801071CC(s32, u8, s32);
void func_80107250(s32 arg0, s32 arg1);
void setMenuBackgroundRect(UnkPoly* arg0, s16 x, s16 y, s16 width, s16 height);
void func_8010D584(s16 arg0);
void func_8010E0A8(void);
void func_8010E0B8(void);
void func_80111928(void);
void func_80131EBC(s32 arg0, s32 arg1);
void func_80131ED8(s32 value);
void func_80131EE8(void);
void func_80131F04(void);
s32 func_80131F28(void);
s32 func_80131F38(void);
bool func_80131F68(void);
s16 func_80131F94(void);
s32 func_80133940(void);
s32 func_80133950(void);

#endif
