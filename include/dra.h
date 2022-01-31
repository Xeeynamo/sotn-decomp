#ifndef DRA_H
#define DRA_H
#include "main.h"

typedef struct
{
    unsigned char width;
    unsigned char height;
    unsigned short unk2;
    unsigned char data[0];
} ImgSrc;

typedef struct
{
    s16 cursorX;
    s16 cursorY;
    s16 unk4;
    s16 unk6;
    RECT unk1;
    int w;
    int unk14;
    int unk18;
} MenuContext;

typedef struct
{
    u8 left, top, right, bottom;
    u8 tileLayoutId;
    u8 tilesetId;
    u8 objGfxId;
    u8 objLayoutId;
} RoomHeader;

typedef struct
{
    u16 x, y;
    u16 id : 10;
    u16 unk04_10 : 3;
    u16 unk04_13 : 3;
    u8 unk06;
    u8 unk07;
    u16 unk08;
} ObjLayoutEntry;

typedef struct 
{
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Unkstruct1;

typedef union
{
    s32 data;
    struct
    {
        s16 unk0;
        s16 unk2;
    } Data;
    
} Unkunion1; // big assumption here...

typedef struct
{
    Unkunion1 unk0;
    Unkunion1 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10[7];
    u16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s16 unk50;
    s16 unk52;
} Unkstruct3;

typedef struct
{
    char unk0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Unkstruct4;

typedef struct
{
    u16 unk0;
    u16 unk2;
    u16 state;
    u16 x;
    u16 y;
} ObjectInit;

typedef struct
{
    s32 unk0;
    char unk4[0x30];
    s32 unk34;
    char unk38[0x2C];
    s32 unk64;
    char unk68[0x54];
} Unkstruct5;

extern s32 D_8006BB00;
extern Unkstruct3* D_8006C26C;
extern s32 D_8006C39C;
extern s32 D_8006C3A0;
extern Unkstruct4 D_80072B34;
extern u16 D_80072B3E;
extern s16 D_80072E8A;
extern s16 D_80072E8E;
extern s32 D_80072F2C;
extern s32 D_80073060;
extern s32 D_80073080;
extern s32 g_CurrentRoomHSize;
extern s32 g_CurrentRoomVSize;
extern s32 D_800730AC;
extern s32 g_CurrentRoomLeft;
extern s32 g_CurrentRoomTop;
extern s32 g_CurrentRoomRight;
extern s32 g_CurrentRoomBottom;
extern s32 D_800730C0;
extern s32 D_800730C4;
extern s32 g_CurrentRoomWidth;
extern s32 g_CurrentRoomHeight;
extern Unkstruct5 D_800733D8[];
extern s16 D_80073404;
extern s16 D_80073406;
extern s8  D_80073510;
extern s8  D_80073511;
extern s8  D_80073512;
extern void* D_8007EFD8;
extern POLY_GT4 D_80086FEC[];
extern s32 D_80096ED8[];
extern u32 D_80097364;
extern s32 D_800973B4;
extern POLY_GT4 D_800973B8[];
extern s32 playerX;
extern s32 playerY;
extern s32 D_800973FC;
extern Unkstruct1 D_80097490;
extern u16 D_80097494;
extern s16 D_80097496;
extern s32 g_mapProgramId;
extern s32 D_800974AC;
extern u8  D_8009798A;
extern u8  D_80097A8D;
extern s32 g_playerLevel;
extern s32 g_playerExp;
extern s32 g_playerGold;
extern s32 g_killCount;
extern s32 g_playerHeart;
extern s32 g_playerHeartMax;
extern s32 g_playerHp;
extern s32 g_playerHpMax;
extern s32 g_playerMp;
extern s32 g_playerMpMax;
extern s32 D_80097C20;
extern s32 D_80097C24;
extern s32 g_timeHours;
extern s32 g_timeMinutes;
extern s32 g_timeSeconds;

extern s32 D_800A2438;
extern const char* c_strALUCARD;
extern const char* c_strSTR;
extern const char* c_strCON;
extern const char* c_strINT;
extern const char* c_strLCK;
extern const char* c_strEXP;
extern const char* c_strNEXT;
extern const char* c_strGOLD;
extern const char* c_strLEVEL;
extern const char* c_strTIME;
extern const char* c_strROOMS;
extern const char *c_strKILLS;
extern const char* c_strHP;
extern const char* c_strMP;
extern const char* c_strHEART;
extern const char* c_strSTATUS;
extern const char *c_strButton;
extern const char *c_strCloak;
extern const char *c_strCloak2;
extern const char *c_strExterior;
extern const char *c_strLining;
extern const char *c_strButtonRightHand;
extern const char *c_strButtonLeftHand;
extern const char *c_strButtonJump;
extern const char *c_strButtonSpecial;
extern const char *c_strButtonWolf;
extern const char *c_strButtonMist;
extern const char *c_strButtonBat;
extern const char *c_strNormal;
extern const char *c_strReversal;
extern const char *c_strSound;
extern const char *c_strStereo;
extern const char *c_strMono;
extern const char *c_strWindow;
extern const char *c_strTime;
extern const char* c_strALUCART;
extern const char *c_strSSword;
extern s32 D_800A4B04;
extern s32 D_800A7718;
extern u16 D_800A7734;
extern const char *c_strEquip;
extern const char *c_strSpells;
extern const char *c_strRelics;
extern const char *c_strSystem;
extern const char *c_strFamiliars;
extern const char *c_strFamiliar;
extern const char *c_strSpecial2;
extern RECT c_backbufferClear;
extern u8  D_80137460;
extern s32 D_801375C8;
extern s32 D_801375DC;
extern s32 D_801375FC;
extern s32 D_80137618;
extern s8  D_80137638;
extern s32 D_80137844;
extern s32 D_80137848;
extern s32 D_8013784C;
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 D_80137E4C;
extern s32 D_80137E64;
extern s32 D_80137E68;
extern s32 D_80138F20;
extern s32 D_80138F7C;
extern s16 D_80139000;
extern s16 D_8013901C;
extern s8  D_80139020;
extern s8  D_801390C4;
extern u8  D_801390D8;
extern s16 D_801390DC;
extern s16 D_801390DE;
extern s16 D_801390E0;
extern s16 D_801396EA;
extern u16 D_801396F4;
extern s32 D_8013980C;
extern u8  D_80139810;
extern s32 D_80139828;
extern u16 D_80139868;
extern s16 D_80139A70;
extern u8 D_8013AEEC;
extern s32 D_8013B158;
extern s32 D_8013B3D0;
extern s16 D_8013B3E8[];
extern s32 D_8013B5E8;
extern s32 D_8013B61C;
extern s16 D_8013B658;
extern s32 D_8013B660;
extern s16 D_8013B668;
extern s32 D_8013B694;
extern s32 D_80138784[487];
extern ImgSrc* g_imgUnk8013C200;
extern ImgSrc* g_imgUnk8013C270;

void func_800E4124(s32 arg0);
void func_800E8D24(void);
void func_800E8DF0(void);
void func_800E92E4(void);
void func_800E92F4(void);
void func_800EA5E4(s32);
void func_800EDA70(s32 *arg0);
void func_800EDAE4(void);
s16 func_800EDC80(u8 arg0, s32 arg1);
s16 func_800EDD9C(u8 arg0, s32 arg1);
void func_800EDE78(s32 index);
void func_800F1EB0(s32, s32, s32);
void func_800F2120();
void func_800F223C(void);
void func_800F4994(void);
void func_800F4F48(void);
void func_800F4FD0(void);
bool IsAlucart();
void func_800F53A4(void);
s32 IsSpriteOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* a5);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void func_800F5904(void*, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v, s32 unk1, s32 unk2, bool disableTexShade, s32 unk4);
void func_800F5E68(MenuContext*, s32 iOption, s32 x, s32 y, s32 w, s32 h, s32, s32);
s32 func_800F62E8(s32 arg0);
void DrawMenuChar(s32 ch, int x, int y, void* context);
void DrawMenuStr(const char* str, s32 x, s32 y, MenuContext* context);
void DrawMenuInt(s32 value, s32 x, s32 y, MenuContext*);
void DrawSettingsReverseCloak(MenuContext* context);
void DrawSettingsSound(MenuContext* context);
void DrawPauseMenu(s32 arg0);
void func_800F82F4(void);
void func_800F8858(MenuContext* context);
void func_800FABEC(s32 arg0);
void func_800FAC30(void);
s32 func_800FD664(s32 arg0);
u8 *func_800FD744(s32 arg0);
u8 *func_800FD760(s32 arg0);
s32 func_800FD77C(s32 arg0, s32 arg1);
bool func_800FD7C0(s32, s32);;
void func_800FD874(u16 arg0, s32 arg1);
void func_800FDE00(void);
void func_800FF0A0(s32 arg0);
void func_80102DEC(s32 arg0);
void func_80103EAC(void);
void func_80106590(Unkstruct5*);
void func_801065F4(s16 startIndex);
void func_801071CC(s32, u8, s32);
void func_80107250(s32 arg0, s32 arg1);
void SetPolyRect(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height);
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
s32 func_80132134();
s32 func_80132264();
s32 func_801324B4(s32, s32, s32);
s32 func_801326D8();
void func_8013271C(void);
void func_80132760(void);
void func_801337B4(void);
s32 func_80133940(void);
s32 func_80133950(void);
void func_8013415C();
void func_801361F8();

#endif
