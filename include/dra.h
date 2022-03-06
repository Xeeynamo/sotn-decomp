#ifndef DRA_H
#define DRA_H
#include "main.h"

typedef void (*PfnEntityUpdate)(struct Entity*);

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
    s16 unk18;
    s16 unk1A;
} MenuContext;

typedef struct
{
    u8 tileLayoutId;
    u8 tilesetId;
    u8 objGfxId;
    u8 objLayoutId;
} RoomLoadDef;

typedef struct
{
    u8 left, top, right, bottom;
    RoomLoadDef load;
} RoomHeader;

typedef struct 
{
    s16 pressed;
    s16 previous;
    s16 tapped;
    s16 repeat;
} Pad;

typedef union
{
    s32 value;
    struct
    {
        s16 low;
        s16 high;
    } Data;
    struct
    {
        s8 unk0;
        s8 unk1;
        s16 unk2;
    } Data1;
    
} Unkunion1; // big assumption here...

typedef struct
{
    u8 _[0];
    Unkunion1 posX;
    Unkunion1 posY;
    s32 accelerationX;
    s32 accelerationY;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 palette;
    s8 unk18;
    s8 unk19;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    u16 zPriority;
    u16 objectId;
    PfnEntityUpdate pfnUpdate;
    u16 initState;
    s16 unk2E;
    u16 subId;
    u16 unk32;
    s32 unk34;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    u16 unk44;
    u8 hitboxWidth;
    u8 hitboxHeight;
    u8 unk48;
    u8 unk49;
    s16 unk4A;
    s32 unk4C;
    u16 animationFrameIndex;
    s16 animationFrameDuration;
    s16 animationSet;
    s16 animationFrame;
    s16 unk58;
    s16 unk5A;
    s32 unk5C;
    s32 unk60;
    s32 firstPolygonIndex;
    s16 unk68;
    s16 unk6A;
    u8 unk6C;
    s8 unk6D;
    s16 unk6E;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    u16 unk7C;
    u16 unk7E;
    s16 unk80;
    s16 unk82;
    s8 unk84;
    s8 unk85;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    s32 unk8C;
    s32 unk90;
    u8 unk94;
    u8 unk95;
    s16 unk96;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
} Entity;

typedef struct
{
    char unk0[0xA];
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Unkstruct4;

typedef struct
{
    u16 posX;
    u16 posY;
    u16 flags;
    u16 unk6;
    u16 unk8;
} ObjectInit;

typedef struct
{
    s16 unk0;
    s16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    s16 unkA;
    u16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 hitboxWidth;
    u8 hitboxHeight;
    s32 unk24;
} Unkstruct5;

typedef struct
{
    u_long	tag;
    s8 unk4, unk5, unk6, unk7;
    s16 unk8, unkA;
    s16 unkC, unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s8 unk24;
    s8 unk25;
    s8 unk26;
    s8 unk27;
    s8 unk28;
    s8 unk29;
    s8 unk2A;
    s8 unk2B;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
} Unkstruct6; // This is most likely POLY_GT4

typedef struct
{
    u_long	tag;
    s8 unk4, unk5, unk6, unk7;
    s16 unk8, unkA;
    s16 unkC, unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s8 unk1E;
    s8 unk1F;
    s16 unk20;
    s16 unk22;
    s8 unk24;
    s8 unk25;
    s8 unk26;
    s8 unk27;
    s8 unk28;
    s8 unk29;
    s8 unk2A;
    s8 unk2B;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
} Unkstruct7;

typedef struct
{
    void *addr1;
    void *addr2;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
} Unkstruct8;

typedef struct
{
    u16 animationSet;
    u16 zPriority;
    u16 unk4;
    u16 palette;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u32 unkC;
    u8* unk10;
} ObjInit2;

typedef struct
{
    u16 programId;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
} Unkstruct10;

// main
extern Unkstruct5* D_8003C704;
extern u16 D_8003C708;
extern s32 D_8003C730;
extern s32 D_8003C734;
extern void (*D_8003C744)(s32, s32);
extern void (*g_pfnUpdateStageEntities)(void);
extern RoomHeader* D_8003C784;
extern void (*g_pfnPlaySfx)(s32);
extern void (*g_pfnFreePolygons)(s32);
extern Unkstruct5* D_8003C808;
extern void (*D_8003C848)(s32, s32);
extern s32 D_8003C8C4;
extern s32 g_roomCount;
extern s32 g_CurrentPlayableCharacter;
extern s32 g_SettingsCloakMode;
extern s32 g_SettingsSoundMode;
extern s32 D_8003CACC;

// dra
#define PAD_COUNT 2
#define PAD_L2          0x0001
#define PAD_R2          0x0002
#define PAD_L1          0x0004
#define PAD_R1          0x0008
#define PAD_TRIANGLE    0x0010
#define PAD_CIRCLE      0x0020
#define PAD_CROSS       0x0040
#define PAD_SQUARE      0x0080
#define PAD_SELECT      0x0100
#define PAD_L3          0x0200
#define PAD_R3          0x0400
#define PAD_START       0x0800
#define PAD_UP          0x1000
#define PAD_RIGHT       0x2000
#define PAD_DOWN        0x4000
#define PAD_LEFT        0x8000

#define RENDERFLAGS_NOSHADOW 2
#define PLAYER_ALUCARD 0
#define PLAYER_RICHTER 1
#define MAX_GOLD 999999
#define HEART_VESSEL_INCREASE 5
#define HEART_VESSEL_RICHTER 30
#define LIFE_VESSEL_INCREASE 5
#define FALL_GRAVITY 0x4000
#define FALL_TERMINAL_VELOCITY 0x60000

#define TOTAL_ENTITY_COUNT 256
#define MaxEntityCount 32
#define EntityExplosionID 2
#define EntityCandleDropID 3
#define EntityCandleHeartDropID 10

#define PROGRAM_NO0 0x00
#define PROGRAM_NO1 0x01
#define PROGRAM_LIB 0x02
#define PROGRAM_CAT 0x03
#define PROGRAM_NO2 0x04
#define PROGRAM_CHI 0x05
#define PROGRAM_DAI 0x06
#define PROGRAM_NP3 0x07
#define PROGRAM_CEN 0x08
#define PROGRAM_NO4 0x09
#define PROGRAM_ARE 0x0A
#define PROGRAM_TOP 0x0B
#define PROGRAM_NZ0 0x0C
#define PROGRAM_NZ1 0x0D
#define PROGRAM_WRP 0x0E
#define PROGRAM_NO1_ 0x0F
#define PROGRAM_NO0_ 0x10
#define PROGRAM_DRE 0x12
#define PROGRAM_BO6 0x18
#define PROGRAM_ST0 0x1F
#define PROGRAM_MAD 0x40
#define PROGRAM_NO3 0x41
#define PROGRAM_INVERTEDCASTLE_FLAG 0x20

extern s32 D_8006BB00;
extern s32 D_8006C374;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern Entity* D_8006C3B8;
extern Unkstruct4 D_80072B34;
extern s32 D_80072F2C;
extern s32 D_80073060;
extern s32 D_80073080;
extern u16 D_8007308E;
extern s16 D_80073092;
extern u16 g_CurrentRoomHSize;
extern u16 g_CurrentRoomVSize;
extern s32 D_800730AC;
extern s32 g_CurrentRoomLeft;
extern s32 g_CurrentRoomTop;
extern s32 g_CurrentRoomRight;
extern s32 g_CurrentRoomBottom;
extern s32 g_CurrentRoomX;
extern s32 g_CurrentRoomY;
extern s32 g_CurrentRoomWidth;
extern s32 g_CurrentRoomHeight;
extern Entity D_800733D8[TOTAL_ENTITY_COUNT];
extern s16 D_800733DA;
extern s16 D_800733DE;
extern s16 D_80073404;
extern s16 D_80073406;
extern s8  D_80073510;
extern s8  D_80073511;
extern s8  D_80073512;
extern Entity D_800762D8[]; // D_800733D8 + 0x40
extern Unkstruct8 g_CurrentRoomTileLayout;
extern Entity D_8007A958[];
extern Entity D_8007D858[];
extern u16 D_80097408;
extern s32 D_80097428[];
extern Entity D_8007EF1C;
extern void* D_8007EFD8;
extern POLY_GT4 D_80086FEC[];
extern s32 playerX;
extern s32 playerY;
extern u32 g_randomNext;
extern s32 D_800973FC;
extern s32 D_80097410;
extern s32 D_80097414;
extern Pad g_pads[];
extern s16 D_80097496;
extern s32 g_mapProgramId;
extern s32 D_800974AC;
extern s32 D_80097908;
extern s32 D_8009790C;
extern u8  D_8009796E;
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
extern s32 D_80097C98;

extern s32 D_800A2438;
extern Unkstruct10 D_800A2464[];
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
extern s16 D_800BD07C[];
extern u8  D_80137460;
extern RoomLoadDef* D_801375BC;
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
extern s32 D_80137970;
extern s32 D_80137974;
extern u32 D_80137978;
extern u32 D_8013797C;
extern s32 D_80137980;
extern s32 D_80137984;
extern u32 D_80137988;
extern u32 D_8013798C;
extern s32 D_80137990;
extern s32 D_80137994;
extern s32 D_80137E4C;
extern s32 D_80137E64;
extern s32 D_80137E68;
extern s32 D_80138F20;
extern s32 D_80138F28;
extern s32 D_80138F7C;
extern s16 D_80139000;
extern s16 D_80139008;
extern s16 D_8013901C;
extern u8  D_80139020;
extern s8  D_801390C4;
extern u8  D_801390D8;
extern s16 D_801390DC;
extern s16 D_801390DE;
extern s16 D_801390E0;
extern s16 D_801396EA;
extern u16 D_801396F4;
extern s32 D_801397FC;
extern s32 D_8013980C;
extern u8  D_80139810;
extern s32 D_80139828;
extern s32 D_80139834[];
extern s16 D_80139868;
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
extern u8  D_8013B680;
extern s8 D_8013B684;
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
s32 func_800EDD9C(u8 arg0, s32 arg1);
void FreePolygons(s32 index);
s32 func_800F087C(u32, u32);
bool SetNextRoomToLoad(u32 chunkX, u32 chunkY);
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
void DrawMenuChar(char ch, int x, int y, MenuContext* context);
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
void func_80106590(Entity*);
void func_801065F4(s16 startIndex);
void func_801071CC(POLY_GT4 *poly, u8, s32);
void func_80107250(POLY_GT4 *poly, s32 arg1);
void func_80107360(POLY_GT4 *poly, s32 x, s32 y, s32 width, s32 height, u8 u, u8 v);
void SetPolyRect(POLY_GT4 *poly, s32 x, s32 y, s32 width, s32 height);
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
s32 func_801326D8();
void func_8013271C(void);
void func_80132760(void);
void func_801337B4(void);
s32 func_80133940(void);
s32 func_80133950(void);
void func_8013415C();
void func_801361F8();

#endif
